#include "gaem_engine.h"
#include "gaem_actors.h"
#include "gaem_app.h"

class Actor {
  public:
    Coord Position;
    Coord Velocity;
    Coord Speed;

    // Base Constructor
    Actor() { }
};

class Player: public Actor {
  protected:
    int JumpTimer;
    static const int MaxJumpTime = 2;

  public:
    // Base Constructor
    Player() {
    }

    // Constructor
    Player(int x, int y) {
      JumpTimer = 0;
      Position = Coord(x, y);
    }

    // Update
    void Update( ) {
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

      // Jumping
      if (digitalRead(but2) == HIGH) {
        if (Position.Y > 0) {
          Position.Y--;
        }
      } else if (Position.Y < dispHeight - 1) {
        Position.Y++;
      }

      // Save position to display
      Registry::Display[Position.X][Position.Y].Disp_Mode = DISP_ON;
    }
};

class Threat: public Actor {
  public:
    bool InPlay;
    // Base Constructor
    Threat() { }

    // Constructor
    Threat(int x, int y) {
      Position = Coord(x, y);
      InPlay = true;
    }

    void Update( ) {
      if (!InPlay) {
        return;
      }

      //Display[Position.X][Position.Y].Disp_Mode = DISP_ON;
    }
};
