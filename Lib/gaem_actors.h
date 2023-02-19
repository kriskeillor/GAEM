/***********************************************************************
  GAEM
  General Arduino Exploration Machine

  Proto-board shield for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.

  Created by Kris Keillor for the Bellingham MakerSpace
  v1.0 2023-02-18 KGK
***********************************************************************/

#ifndef GAEM_ACTORS_H_
#define GAEM_ACTORS_H_

// Out-of-Bounds behavior
enum OOB_BEHAVIOR_T { BIND, CULL };
// Collision behavior
enum COLLIDE_BEHAVIOR_T { KILL, DIE };
// End (exit or death) behavior
enum END_BEHAVIOR_T { SCORE, END_GAME };

class Actor;
class Player;
class Threat;

#endif
