/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-23 KGK
*/

// ATmega32u4 header file
#include <avr/io.h>

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

void Setup_Board(void) {
  // HARDWARE SETUP
  // initialize digital pins as an outputs for LEDs.
  pinMode(LED_BUILTIN, OUTPUT);
  for (int pinN = LED_OFFSET; pinN <= LED_OFFSET + LED_COUNT; pinN++) {  
    pinMode(pinN, OUTPUT);
  }

  // initialize digital pins as an inputs for buttons.
  // TODO: enable pulldown resistors (after hardware revision to v1.2)
  for (int butN = BUT_OFFSET; butN <= BUT_OFFSET + BUT_COUNT; butN++) {
    pinMode(butN, INPUT);
  }
}
