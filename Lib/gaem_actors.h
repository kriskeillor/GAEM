/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-18 KGK
*/

#ifndef GAEM_ACTORS_H_
#define GAEM_ACTORS_H_

// Constants for Player Jump Interrupt & Timer
const int Player_JT_PS = 1024;                 // Prescaler Value (for Timer Freq of 15625 Hz)
const int Player_JT_OC = 30;                   // Output Compare limit (for ~520 millis)
// Registers for Player Jump Interrupt

// Out-of-Bounds behavior
enum OOB_BEHAVIOR_T { BIND, CULL };
// Collision behavior
enum COLLIDE_BEHAVIOR_T { KILL, DIE };
// End (exit or death) behavior
enum END_BEHAVIOR_T { SCORE, END_GAME };

class Actor;
class Player;
class Threat;

void Setup_Player_Jump_Interrupt();

void Setup_Player_Fall_Timer();

#endif
