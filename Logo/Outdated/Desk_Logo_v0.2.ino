// the setup function runs once when you press reset or power the board

#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR //make Arduino Due happy
#endif // !PSTR

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 255, 255), matrix.Color(255, 255, 255), matrix.Color(255, 255, 255)
};

void setup() {

  //Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);

}

int x = matrix.width();
int pass = 0;

// the loop function runs over and over again until power down or reset
void loop() {
  char scrollText[] = "{";
  int scrollLen = strlen(scrollText) * - 95; //time between scroll animation
  matrix.fillScreen(matrix.Color(0, 0, 200));
  matrix.setCursor(x, 0);
  matrix.print(scrollText);
  if (--x < scrollLen) {
    x = matrix.width();
    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(10); //scroll speed == lower is faster
}
