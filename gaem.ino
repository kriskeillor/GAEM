/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

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
  // HARDWARE SETUP
  Setup_Board();
  Setup_Player_Jump_Interrupt();
  Setup_Player_Fall_Timer();

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
    di++;
    Registry::Reg_Draw();
    delay(Registry::DRAW_TICK);
  }
}
