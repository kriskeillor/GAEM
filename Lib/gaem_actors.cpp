/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-23 KGK
*/

#include <avr/io.h>
#include <avr/interrupt.h>
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

/*      // Falling
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
*/
      CheckBounds();
    }

    // Jumping
    static void ISR_Jump(void) {
      if (Registry::GamePlayer.Position.Y == WALL_FLOOR) {
        Registry::GamePlayer.Position.Y--;
        /* (general interrupt, but base class Actor does not declare Position static)
              TODO: Consider changing Player to be Static                       */

        // Enable player's falling timer, Timer 1, with prescaler 1024
        TCCR1B |= (1 << CS02) | (1 << CS00);
      } 
      else { /* else, player is in the air, can't jump */ }

      return NULL;
    }

    // Falling
    static void ISR_Fall_Timer(void) {
      // Disable global interrupts
      cli();

      // Move position of player via registry 
      Registry::GamePlayer.Position.Y++;
      /* (static ISR, but base class Actor does not declare Position static)
              TODO: Consider changing Player to be Stati                  */

      // Disable Timer 1 compare match interrupt
      TIMSK1 &= ~(1 << OCIE0A);
      // Enable global interrupts
      sei();
    }
    // Fall after the timer ends
};

// Player fall timer callback interrupt routine
ISR(TIMER1_COMPA_vect) {
  // Call player ISR from NVIC-known interrupt vector
  Player::ISR_Fall_Timer();
}

void Setup_Player_Jump_Interrupt(void) {
  attachInterrupt(digitalPinToInterrupt(7), Player::ISR_Jump, FALLING);

  return NULL;
}

void Setup_Player_Fall_Timer(void) {
  // Zero out Timer/Counter Control Registers A & B
  TCCR1A = 0x00;
  TCCR1B = 0x00;

  // Set prescaler to 1024
  TCCR1B |= (1 << CS02) | (1 << CS00);

  // Set initial counter value
  TCNT1 = 0;

  // Set compare match value
  OCR1A = Player_JT_OC;

  // Enable output compare match interrupt
  TIMSK1 = (1 << OCIE0A);

  // Set global interrupt enable bit
  sei();

  return NULL;
}

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
