//*****  RossRobotics.com
//  4-16-22
//    -Initial code
//    -Removed needless functions
//  4-22-22
//    -After 4 days, finally got a button to change patterns
//    -Added a solid color pattern that changes color via a slide pot
//      +'slide pot' is a GUI slide pot graphic

#include "FastLED.h"

// define data pins here
#define DATA_PIN    6
// define button pin here
#define BTN_PIN     2

#define NUM_ROWS 8
#define NUM_COLS 32
#define NUM_LEDS NUM_ROWS * NUM_COLS
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define BRIGHTNESS        60
int FRAMES_PER_SECOND = 60;

/////***************color changer***************/////////////////////
#define MAX_BRIGHTNESS 255      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 25       // set to a minimum of 25%

const int brightnessInPin = A0;  // The Analog input pin that the brightness control potentiometer is attached to.
const int speedInPin = A1;       // Analog input pin that the speed control potentiometer is attached to.
const int colourInPin = A2;
int mappedHue;
//END COLOR CHANGER


void setup() {
  pinMode(BTN_PIN, INPUT);

  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();

// define patterns here, e.g. (full list):
SimplePatternList gPatterns = {fireBlue, fireRed, color};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(2000 / FRAMES_PER_SECOND);

  // check oif button pressed
  if (digitalRead(BTN_PIN) == HIGH) {
    // if button pressed, switch pattern
    nextPattern();
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern() {
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

DEFINE_GRADIENT_PALETTE(firepal) { // белая, желтая, красная палитра
  0,  0,  0,  0, //black
  50,  0,  0,  255, // red
  190,  0,  191,  255, //yellow
  255,  255,  255,  255 // white
};

DEFINE_GRADIENT_PALETTE(firepal2) { // белая, желтая, красная палитра
  0,  0,  0,  0, //black
  32,  255,  0,  0, // red
  190,  255,  255,  0, //yellow
  255,  255,  255,  255 // white
};
CRGBPalette16 myPal = firepal;
CRGBPalette16 myPal2 = firepal2;
uint16_t XY (uint8_t x, uint8_t y) {
  return (y * NUM_COLS + x); // для эмулятора
}

void fireBlue() {
  int scalexy = 60;  // масштаб
  float speed = 1.2; //скорость

  float a = millis() * speed;
  for (int i = 0; i < NUM_COLS; i++) {
    for (int j = 0; j < NUM_ROWS; j++) {
      leds[XY(i, j)] =
        ColorFromPalette(myPal, qsub8(inoise8(i * scalexy, j * scalexy + (int)a, (int)a / 2), abs8(i - (NUM_ROWS - 1)) * 255 / (NUM_ROWS + 2)), 125);
    }
  }
}

void fireRed() {
  int scalexy = 60;  // масштаб
  float speed = 1.2; //скорость

  float a = millis() * speed;
  for (int i = 0; i < NUM_COLS; i++) {
    for (int j = 0; j < NUM_ROWS; j++) {
      leds[XY(i, j)] =
        ColorFromPalette(myPal2, qsub8(inoise8(i * scalexy, j * scalexy + (int)a, (int)a / 2), abs8(i - (NUM_ROWS - 1)) * 255 / (NUM_ROWS + 2)), 125);
    }
  }
}

void color() {
  for (int i = 0; i < NUM_LEDS; i++) {
    mappedHue = map(analogRead(colourInPin), 0, 1023, 0, 255);
    // Set the i'th led to the chosen colour
    leds[i] = CHSV(mappedHue, 255, 255);
  }
}
//
//void sinelon() {
//  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16(13, 0, NUM_LEDS);
//  leds[pos] += CHSV( gHue, 255, 192);
//}
