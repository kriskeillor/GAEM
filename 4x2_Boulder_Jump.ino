/*
  Boulder Jump game

  Use the left and right buttons and jump button to evade the boulders!
*/

/**********************************************************************/
// Header Files
#include "./Board/gaem_board.h"
#include "./Lib/gaem_engine.h"
#include "./Lib/gaem_actors.h"
#include "./Lib/gaem_app.h"

// Source Files
#include "./Board/gaem_board.cpp"
#include "./Lib/gaem_engine.cpp"
#include "./Lib/gaem_actors.cpp"
#include "./Lib/gaem_app.cpp"
/**********************************************************************/

/**********************************************************************/
// GLOBAL VARIABLES
//static App_Register Register;

// FUNCTIONS
void setup() {
  // TODO: Move to board source
  // HARDWARE SETUP
  // initialize digital pins as an outputs for LEDs.
  pinMode(LED_BUILTIN, OUTPUT);
  for (int pinN = ledOffset; pinN <= ledOffset + ledCount; pinN++) {  
    pinMode(pinN, OUTPUT);
  }

  // initialize digital pins as an inputs for buttons.
  // TODO: enable pulldown resistors (after hardware revision to v1.2)
  for (int butN = butOffset; butN <= butOffset + butCount; butN++) {
    pinMode(butN, INPUT);
  }

  Serial.begin(9600);
  delay(100);
  Serial.println("Begin Debugging Run");

  Registry::Reg_Init();
}
/**********************************************************************/

/**********************************************************************/
// DRAW FUNCTION
void draw() {
  int pinN = ledOffset;

  for (int x = dispWidth - 1; x >= 0; x--) {
    for (int y = dispHeight - 1; y >= 0; y--) {
      if (Registry::Display[x][y].Disp_Mode == DISP_ON) {
        digitalWrite(pinN, HIGH);
      } else {
        digitalWrite(pinN, LOW);
      }
      // Increment pin counter used to map digital outputs
      pinN++;
    }
  }
}

// CLEAR DISPLAY FUNCTION
void clearDisplay() {
  for (int x = 0; x < dispWidth; x++) {
    for (int y = 0; y < dispHeight; y++) {
      Registry::Display[x][y].Disp_Mode = DISP_OFF;
    }
  }
}

// GAME LOOP
void loop() {
  // Debug LED
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Enter Main Loop");

  // Clear the LED Display settings
  clearDisplay();

  // Update Player
  Registry::GamePlayer.Update();

  // Update Threats
  for (int i = 0; i < Registry::MAX_THREATS; i++) {
    Registry::GameThreats[i].Update();
  }

  // Scan for collisions

  // Debug LED
  digitalWrite(LED_BUILTIN, LOW);
  int di = 0;
  while (di < Registry::DrawCallsPerTick) {
    draw();
    di++;
    delay(Registry::LoopTick / Registry::DrawCallsPerTick);                      // wait for 1s
  }
}
