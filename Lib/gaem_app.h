#ifndef GAEM_APP_H_
#define GAEM_APP_H_

#include "gaem_engine.h"
#include "gaem_actors.h"

enum APP_STATE_T { STARTUP, DEMO, EASY, ENDLESS };

namespace Registry {
  // APP CONSTANTS
  const int MaxThreats = 4;
  const int LoopTick = 250;           // Game refresh rate in ms
  const int DrawCallsPerTick = 5;

/*
  // APP VARIABLES
  static bool DrawInverted;
  static APP_STATE_T State;

  // APP OBJECTS
  static Player GamePlayer;
  static Threat GameThreats[4];
  static Disp_Pixel Display[4][2];

  // APP METHODS
  static void Registry_Init() { }
  */
};


#endif
