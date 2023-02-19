#include "gaem_board.h"

struct Disp_Pixel {
  public:
    DISP_MODE_T Disp_Mode;
    int Pin;              // Hardware pin for controlling output
    int Frequency;        // Hz for Blink and Pulse mode
    int Duty;             // used for Blink only
    int MaxBrightness;    // used for Pulse only
    int MinBrightness;    // used for Pulse only

    // Base Constructor
    Disp_Pixel( ) {
      Disp_Mode = DISP_OFF;
      Pin = 0;
      Frequency = 0;
      Duty = 0;
      MaxBrightness = 0;
      MinBrightness = 0;
    }

    // Full Constructor
    Disp_Pixel(
      DISP_MODE_T disp_mode,
      int pin,
      int freq,
      int duty,
      int maxBrightness,
      int minBrightness) {
        Pin = pin;
        Disp_Mode = disp_mode;
        Frequency = freq;
        Duty = duty;
        MaxBrightness = maxBrightness;
        MinBrightness = minBrightness;
    }
};
