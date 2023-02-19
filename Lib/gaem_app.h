#ifndef GAEM_APP_H_
#define GAEM_APP_H_

#include "../Board/gaem_board.h"
#include "gaem_engine.h"
#include "gaem_actors.h"

enum APP_STATE_T { STARTUP, DEMO, EASY, ENDLESS };

namespace Registry {
  // APP CONSTANTS
  const int MAX_THREATS = 4;
  const int LoopTick = 250;           // Game refresh rate in ms
  const int DrawCallsPerTick = 5;

  // APP VARIABLES
  bool DrawInverted;
  
  extern APP_STATE_T State;

  // APP OBJECTS
  extern Player GamePlayer;
  extern Threat GameThreats[MAX_THREATS];
  extern Disp_Pixel Display[dispWidth][dispHeight];

  // APP METHODS
  void Registry_Init();
};

#endif
