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
  const int MAX_THREATS = 4;
  const int LOOP_TICK = 250;            // Game refresh rate in ms
  const int DrawCallsPerTick = 5;

  // APP VARIABLES
  bool DrawInverted;
  int Score = 0;
  int ThreatSpawnTime = LOOP_TICK * 10; // Threat spawn rate in ms
  int ThreatSpawn_t = 0;                // Threat spawning counter

  extern APP_STATE_T State;

  // APP OBJECTS
  extern Player GamePlayer;
  extern Threat GameThreats[MAX_THREATS];
  extern Disp_Pixel Display[DISP_WIDTH][DISP_HEIGHT];

  // APP METHODS
  void Reg_Init();
  void Reg_Update();
  void Reg_Draw();
};

#endif
