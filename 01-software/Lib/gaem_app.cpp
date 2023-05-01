/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-23 KGK
*/

#include "gaem_engine.h"
#include "gaem_actors.h"
#include "gaem_app.h"

namespace Registry {
// APP VARIABLES
  //DrawInverted = false;
  APP_STATE_T State = STARTUP;

  // APP OBJECTS
  Player GamePlayer;
  Threat GameThreat;
  Disp_Pixel Display[4][2];

  // APP METHODS
  // INITIALIZE
  void Reg_Init(void) {
    // Init Variables
    DrawInverted = false;
    State = STARTUP;

    // Init Actors
    GamePlayer = Player(3, 1);

    // Init Display
    // TODO: Move to hardware init
    for (int x = 0; x < DISP_WIDTH; x++) {
      for (int y = 0; y < DISP_HEIGHT; y++) {
        Display[x][y] = Disp_Pixel();
      }
    }

    // Start the game!
    State = ENDLESS;
  }

  // UPDATE FUNCTION
  void Reg_Update() {
    // Update Player
    GamePlayer.Update();

    // Update Threats
    GameThreat.Update();

    // Scan for collisions
    if (GamePlayer.Position.X == GameThreat.Position.X && 
        GamePlayer.Position.Y == GameThreat.Position.Y) {
      GamePlayer.Collide(&GameThreat);
      GameThreat.Collide(&GamePlayer);
    }

    switch(State) {
      case STARTUP:
        // TODO: intro animation :)
        break;
      case ENDLESS:
        // Spawn Threats
        ThreatSpawn_t += LOOP_TICK;
        if (ThreatSpawn_t >= ThreatSpawnTime) {
          if (!GameThreat.InPlay) {
            ThreatSpawn_t = 0;
            GameThreat = Threat(0, 1);
          }
        }
        break;
      case GAMEOVER:
        Serial.print("Your score was: ");
        Serial.println(Score);
        State = IDLE;
        break;
      case IDLE:
        break;
    }
  }

  // CLEAR DISPLAY FUNCTION
  void Reg_Clear_Display() {
    for (int x = 0; x < DISP_WIDTH; x++) {
      for (int y = 0; y < DISP_HEIGHT; y++) {
        Registry::Display[x][y].Disp_Mode = DISP_OFF;
      }
    }
  }

  // DRAW DISPLAY FUNCTION
  void Reg_Draw(void) {
    Reg_Clear_Display();

    GamePlayer.Draw();
    GameThreat.Draw();

    int pinN = ledOffset;
    for (int x = DISP_WIDTH - 1; x >= 0; x--) {
      for (int y = DISP_HEIGHT - 1; y >= 0; y--) {
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
};


