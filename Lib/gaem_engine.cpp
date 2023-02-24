/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-23 KGK
*/

#include "gaem_engine.h"

// ENGINE ENUMS, STRUCTS, & CLASSES
struct Coord {
  public:
    int X;
    int Y;

    Coord() {                  // Base Constructor; sets to the origin.
      X = 0;
      Y = 0;
    }

    Coord(int x, int y) {      //      Constructor
      X = x;
      Y = y;
    }
};

