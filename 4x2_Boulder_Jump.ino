/*
  Boulder Jump game

  Use the left and right buttons and jump button to evade the boulders!
*/

/**********************************************************************/
// BOARD DEFINITION
// LED Output Pins
const int ledOffset = 5;
const int ledCount = 8;
// LED Display
const int dispWidth = 4;
const int dispHeight = 2;
// Buttons
const int butOffset = 19;
const int butCount = 3;
const int but1 = 20;
const int but2 = 21;
const int but3 = 19;  // Button 3 is routed back to input 19
/**********************************************************************/

/**********************************************************************/
// BOARD
//    ENUMS & STRUCTS
// <None as of yet. >

/**********************************************************************/
// ENGINE
//    ENUMS & STRUCTS
struct Coord {
  public:
    int X;
    int Y;

    Coord::Coord() {                  // Base Constructor; sets to the origin.
      X = 0;
      Y = 0;
    }

    Coord::Coord(int x, int y) {      //      Constructor
      X = x;
      Y = y;
    }
};


/**********************************************************************/

/**********************************************************************/
// LIBRARY CLASSES
class ButtonPad {
  public:
    ButtonPad::ButtonPad() { }
};

// LED
enum LED_MODE {
  LED_OFF,
  LED_BLINK,
  LED_PULSE,
  LED_ON
};

struct LED_Pixel {
  public:
    LED_MODE Led_Mode;
    int Pin;
    int Frequency;        // Hz for Blink and Pulse mode
    int Duty;             // used for Blink only
    int MaxBrightness;    // used for Pulse only
    int MinBrightness;    // used for Pulse only

    // Base Constructor
    LED_Pixel::LED_Pixel( ) {
      Led_Mode = LED_OFF;
      Pin = 0;
      Frequency = 0;
      Duty = 0;
      MaxBrightness = 0;
      MinBrightness = 0;
    }

    // Full Constructor
    LED_Pixel::LED_Pixel(
      LED_MODE led_mode,
      int pin,
      int freq,
      int duty,
      int maxBrightness,
      int minBrightness) {
        Pin = pin;
        Led_Mode = led_mode;
        Frequency = freq;
        Duty = duty;
        MaxBrightness = maxBrightness;
        MinBrightness = minBrightness;
    }
};
/**********************************************************************/

// APP ENUMS & STRUCTS
enum State {
  STARTUP,
  DEMO,
  EASY,
  ENDLESS
};
/**********************************************************************/


/**********************************************************************/
// APP CONSTANTS
const int MaxThreats = 4;
const int LoopTick = 500;           // Game refresh rate in ms
static LED_Pixel Display[4][2];
/**********************************************************************/

/**********************************************************************/
// ENGINE CLASSES
class Actor {
  public:
    // Base Constructor
    Actor::Actor() { }
    Coord Position;
    Coord Velocity;
    Coord Speed;
};

class Player: public Actor {
  public:
    // Base Constructor
    Player::Player() {
    }

    // Constructor
    Player::Player(int x, int y) {
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
      Display[Position.X][Position.Y].Led_Mode = LED_ON;
    }

  protected:
    int JumpTimer;
    static const int MaxJumpTime = 2;
};

class Threat: public Actor {
  public:
    bool InPlay;
    // Base Constructor
    Threat::Threat() { }

    // Constructor
    Threat::Threat(int x, int y) {
      Position = *(new Coord(x, y));
      InPlay = true;
    }

    void Update( ) {
      if (!InPlay) {
        return;
      }

      Display[Position.X][Position.Y].Led_Mode = LED_ON;
    }
};
/**********************************************************************/

/**********************************************************************/
// ADDITIONAL APP CONSTANTS
static Player GamePlayer;
static Threat GameThreats[4];
/**********************************************************************/

/**********************************************************************/
// GAME SETUP
// the setup function runs once when you press reset or power the board
void setup() {
  // HARDWARE SETUP
  // initialize digital pins as an outputs for LEDs.
  pinMode(LED_BUILTIN, OUTPUT);
  for (int pinN = ledOffset; pinN <= ledOffset + ledCount; pinN++) {
    pinMode(pinN, OUTPUT);
  }

  // initialize digital pins as an inputs for buttons.
  // TODO: enable pulldown resistors (after hardware revision)
  for (int butN = butOffset; butN <= butOffset + butCount; butN++) {
    pinMode(butN, INPUT);
  }

  Serial.begin(9600);
  delay(100);
  Serial.println("Begin Debugging Run");

  // MEMORY SETUP
  // Game
  static State GameState = STARTUP;

  // Initialize player
  GamePlayer = Player(3, 0);

  // Initialize display
  for (int x = 0; x < dispWidth; x++) {
    for (int y = 0; y < dispHeight; y++) {
      Display[x][y] = LED_Pixel();
    }
  }
  // Hard sets
  // Currently unused
  /*Display[0][0].Pin = 11;
  Display[0][1].Pin = 12;
  Display[1][0].Pin = 9;
  Display[1][1].Pin = 10;
  Display[2][0].Pin = 7;
  Display[2][1].Pin = 8;
  Display[0][0].Pin = 5;
  Display[0][1].Pin = 6;*/
}
/**********************************************************************/

/**********************************************************************/
// GAME LOOP
void draw() {
  int pinN = ledOffset;

  for (int x = dispWidth - 1; x >= 0; x--) {
    for (int y = dispHeight - 1; y >= 0; y--) {
      if (Display[x][y].Led_Mode == LED_ON) {
        digitalWrite(pinN, HIGH);
      } else {
        digitalWrite(pinN, LOW);
      }
      // Increment pin counter used to map digital outputs
      pinN++;
    }
  }
}

void clearDisplay() {
  for (int x = 0; x < dispWidth; x++) {
    for (int y = 0; y < dispHeight; y++) {
      Display[x][y].Led_Mode = LED_OFF;
    }
  }
}

int testX = 0;
int testY = 0;

void loop() {
  // Debug LED
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Enter Main Loop");

  // Clear the LED Display settings
  clearDisplay();

  // Update Player
  GamePlayer.Update();

  // Update Threats
  for (int i = 0; i < MaxThreats; i++) {
    GameThreats[i].Update();
  }

  draw();

  // Debug LED
  digitalWrite(LED_BUILTIN, LOW);
  delay(LoopTick);                      // wait for 1s
}
