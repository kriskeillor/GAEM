#include "gaem_engine.h"
#include "gaem_actors.h"
#include "gaem_app.h"

namespace Registry {
  // APP VARIABLES
  static bool DrawInverted;
  static APP_STATE_T State;

  // APP OBJECTS
  static Player GamePlayer;
  static Threat GameThreats[4];
  static Disp_Pixel Display[4][2];

  // APP METHODS
  static void Registry_Init() { }
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

/*
// Allocate memory for static variables
//    /!\     (deprecated)     /!\
bool App_Register::DrawInverted;
APP_STATE_T App_Register::AppState;
Player App_Register::GamePlayer;
Threat App_Register::GameThreats[4];
Disp_Pixel App_Register::Display[4][2];
*/
