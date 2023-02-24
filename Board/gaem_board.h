/*
  # GAEM
  ## General Arduino Exploration Machine
  Perma-proto interface for the Arduino Micro.
  Adds three buttons and a 4x2 LED display.
  https://github.com/kriskeillor/GAEM/

  v1.0 2023-02-18 KGK
*/

#ifndef GAEM_BOARD_H_
#define GAEM_BOARD_H_

/* BOARD DEFINITION CONSTANTS */
// LED Output Pins
const int ledOffset = 5;
const int ledCount = 8;
// LED Display
const int DISP_WIDTH = 4;
const int DISP_HEIGHT = 2;
const int WALL_LEFT = 0;
const int WALL_RIGHT = DISP_WIDTH - 1;
const int WALL_CEIL = 0;
const int WALL_FLOOR = DISP_HEIGHT - 1;
// Buttons
const int butOffset = 19;
const int butCount = 3;
const int but1 = 20;
const int but2 = 21;
const int but3 = 19;      // Button 3 is routed back to input 19

/* BOARD UTILITY CLASSES */
enum DISP_MODE_T {
  DISP_OFF,
  DISP_BLINK,
  DISP_PULSE,
  DISP_ON
};

struct Disp_Pixel;

#endif
