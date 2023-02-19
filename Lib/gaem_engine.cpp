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

