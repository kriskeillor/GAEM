#include "gaem_engine.h"
#include "gaem_actors.h"
#include "gaem_app.h"

namespace Registry {
// APP VARIABLES
  //DrawInverted = false;
  APP_STATE_T State = STARTUP;
  
  // APP OBJECTS
  Player GamePlayer;
  Threat GameThreats[4];
  Disp_Pixel Display[4][2];

  // APP METHODS
  void Reg_Init(void) {
    // Init Variables
    DrawInverted = false;
    State = STARTUP;
    // Init Objects
    GamePlayer = Player(3, 0);  
    for (int x = 0; x < dispWidth; x++) {
      for (int y = 0; y < dispHeight; y++) {
        Display[x][y] = Disp_Pixel();
      }
    }
  }
};


