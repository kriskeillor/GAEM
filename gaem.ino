/*
  Boulder Jump game

  Use the left and right buttons and jump button to evade the boulders!

  v1.0 2023-02-19 KGK
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

  Registry::Reg_Init();
}
/**********************************************************************/

/**********************************************************************/
// GAME LOOP
void loop() {
  // Debug LED
  digitalWrite(LED_BUILTIN, HIGH);

  Registry::Reg_Update();

  // Debug LED
  digitalWrite(LED_BUILTIN, LOW);

  // Draw call processes more frequently than logic update call
  int di = 0;
  while (di < Registry::DrawCallsPerTick) {
    Registry::Reg_Draw();
    di++;
    delay(Registry::LOOP_TICK / Registry::DrawCallsPerTick);
  }
}
