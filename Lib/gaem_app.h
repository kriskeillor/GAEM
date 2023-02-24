/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-23 KGK
*/

#ifndef GAEM_APP_H_
#define GAEM_APP_H_

#include "../Board/gaem_board.h"
#include "gaem_engine.h"
#include "gaem_actors.h"

enum APP_STATE_T { STARTUP, ENDLESS, GAMEOVER, IDLE };

namespace Registry {
  // APP CONSTANTS
  const int LOOP_TICK = 250;			// App update period in ms
  /* The PROGRAM loop runs more frequently than the display. 	*/

  // APP VARIABLES
  extern APP_STATE_T State;
  int Score = 0;
  const int MAX_THREATS = 4;
  int ThreatSpawnTime = LOOP_TICK * 10; // Threat spawn rate in ms
  int ThreatSpawn_t = 0;                // Threat spawning counter

  // APP OBJECTS
  extern Player GamePlayer;
  extern Threat GameThreats[MAX_THREATS];
  extern Disp_Pixel Display[DISP_WIDTH][DISP_HEIGHT];

  // APP METHODS
  void Reg_Init();
  void Reg_Update();
  void Reg_Draw();

  // DISPLAY VARIABLES
  const int DRAW_TICK = 50;				// App draw period in ms
  const int DrawCallsPerTick = LOOP_TICK / DRAW_TICK;
  bool DrawInverted;
};

#endif
