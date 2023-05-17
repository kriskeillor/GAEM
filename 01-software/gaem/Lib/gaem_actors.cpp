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

class Actor {
  public:
    bool InPlay;
    OOB_BEHAVIOR_T OobBehavior;
    COLLIDE_BEHAVIOR_T CollideBehavior;
    END_BEHAVIOR_T EndBehavior;
    
    Coord Position;
    Coord Velocity;
    Coord Speed;

    // Base Constructor
    Actor() { }

    // Update Display
    void Draw() {
      if (InPlay) {
        Registry::Display[Position.X][Position.Y].Disp_Mode = DISP_ON;
      }
    }

    void CheckBounds() {
      switch(OobBehavior) {
        case BIND:
          if (Position.X < WALL_LEFT)         { Position.X = WALL_LEFT; }
          else if (Position.X > WALL_RIGHT)   { Position.X = WALL_RIGHT; }
          if (Position.Y < WALL_CEIL)         { Position.Y = WALL_CEIL; }
          else if (Position.Y > WALL_FLOOR)   { Position.Y = WALL_FLOOR; }
          break;

        case CULL:
          if (Position.X < WALL_LEFT || Position.X > WALL_RIGHT ||
              Position.Y < WALL_CEIL || Position.Y > WALL_FLOOR) {
            Cull();
          }
          break;

        default:
          break;
      }
    }

    void Collide(Actor* collider) {
      switch(CollideBehavior) {
        case KILL:
          collider->Cull();
          break;
        case DIE:
          Cull();
          break;
        default:
          break;
      }
    }

    void Cull() {
      switch(EndBehavior) {
        case SCORE:
            Registry::Score++;
          break;
        case END_GAME:
            Registry::State = GAMEOVER;
          break;
        default:
          break;
      }
      InPlay = false;
    }
};

class Player: public Actor {
  protected:
    static const int MAX_JUMP_T = Registry::LOOP_TICK * 2;
    int Jump_t;
    bool Alive;

  public:
    // Base Constructor
    Player() {
    }

    // Constructor
    Player(int x, int y) {
      Position = Coord(x, y);
      EndBehavior = END_GAME;
      CollideBehavior = DIE;
      OobBehavior = BIND;
      InPlay = true;
      Jump_t = 0;
    }

    // Update
    void Update( ) {
      if (!InPlay) { return; }

      // Moving left/right
      if (digitalRead(but1) == HIGH && digitalRead(but3) == LOW) {
        if (Position.X > 0) {
          Position.X--;
        }
      } else if (digitalRead(but1) == LOW && digitalRead(but3) == HIGH) {
        if (Position.X < 3) {
          Position.X++;
        }
      }

      // Falling
      if (Position.Y == WALL_FLOOR) {
        Jump_t = 0;
      } else if (Position.Y < WALL_FLOOR) {
        Position.Y++;
      } else {
        // Should never get here (negative Pos.Y)
      }

      // Jumping
      if (digitalRead(but2) == HIGH && Jump_t < MAX_JUMP_T) {
        Position.Y--;
        Jump_t += Registry::LOOP_TICK;
      }

      CheckBounds();
    }
};

//Player() : PLAYER_MAX_JUMP ( 500 ) {}

class Threat: public Actor {
  public:
    // Base Constructor
    Threat() { }

    // Constructor
    Threat(int x, int y) {
      Position = Coord(x, y);
      OobBehavior = CULL;
      CollideBehavior = KILL;
      EndBehavior = SCORE;
      InPlay = true;
    }

    void Update( ) {
      if (!InPlay) { return; }

      Position.X++;

      CheckBounds();
    }
};
