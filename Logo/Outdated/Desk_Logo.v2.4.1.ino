//RossRobotics.com
// 4-20-22
//		-Initial Release
//	4-29-22
//    	-After 4 days, finally got a button to change patterns
//		-Bug fixes
//		-Performance 
//	5-15-22
//		-Added a solid color option
//		-color determined by pot by changing the hue

#include <FastLED.h>

#define MAT_TYPE WS2812B   /* Matrix LED type; see FastLED docs for others */
#define MAT_W   32          /* Size (columns) of entire matrix */
#define MAT_H   8          /* and rows */
#define NUM_LEDS 256

#define MAT_PIN 6           /* Data for matrix on D3 on ESP8266 */
#define  MAT_COL_MAJOR       /* define if matrix is column-major (that is pixel 1 is in the same column as pixel 0) */
#define MAT_TOP             /* define if matrix 0,0 is in top row of display; undef if bottom */
#define MAT_LEFT            /* define if matrix 0,0 is on left edge of display; undef if right */
#define MAT_ZIGZAG          /* define if matrix zig-zags ---> <--- ---> <---; undef if scanning ---> ---> ---> */

#define BRIGHT 144           /* brightness; min 0 - 255 max -- high brightness requires a hefty power supply! Start low! */
#define FPS 60              /* Refresh rate */
#define colorPin A2

/* MULTI-PANEL CONFIGURATION -- Do not change unless you connect multiple panels -- See README.md */
/* WARNING -- THIS IS CURRENTLY UNTESTED -- DO NOT ENABLE UNLESS YOU FEEL LIKE BEING MY CRASH TEST MANNEQUIN */
#undef  MULTIPANEL          /* define to enable multi-panel support */
#define PANELS_W    1       /* Number of panels wide */
#define PANELS_H    1       /* Number of panels tall */
#undef  PANEL_TOP           /* define if first panel is upper-left */
#undef  PANEL_ZIGZAG        /* define if panels zig-zag */
/* --- DO NOT CHANGE THESE LINES --- */
#ifndef MULTIPANEL
#define PANELS_H 1
#define PANELS_W 1
#undef PANEL_TOP
#undef PANEL_ZIGZAG
#endif

/* Display size; can be smaller than matrix size, and if so, you can move the origin.
 * This allows you to have a small fire display on a large matrix sharing the display
 * with other stuff. See README at Github. */
const uint16_t rows = MAT_H * PANELS_H;
const uint16_t cols = MAT_W * PANELS_W;
const uint16_t xorg = 0;
const uint16_t yorg = 0;

/* Flare constants */
const uint8_t flarerows = 2;    /* number of rows (from bottom) allowed to flare */
const uint8_t maxflare = 8;     /* max number of simultaneous flares */
const uint8_t flarechance = 50; /* chance (%) of a new flare (if there's room) */
const uint8_t flaredecay = 14;  /* decay rate of flare radiation; 14 is good */

/* This is the map of colors from coolest (black) to hottest. Want blue flames? Go for it! */
const uint32_t colorsRed[] = {
  0x000000,
  0x100000,
  0x300000,
  0x600000,
  0x800000,
  0xA00000,
  0xC02000,
  0xC04000,
  0xC06000,
  0xC08000,
  0x807080
};

const uint32_t colorsBlue[] = {
0x000022,
0x000035,
0x000053,
0x000082,
0x0000CC,
0x0000FF,
0x3333FF,
0x5C5CFF,
0x9797FF,
0xCACAFF,
0xDDDDFF
};
const uint8_t NCOLORS = (sizeof(colorsRed)/sizeof(colorsRed[0]));
const uint8_t BCOLORS = (sizeof(colorsBlue)/sizeof(colorsBlue[0]));

uint8_t pix[rows][cols];
CRGB matrix[MAT_H * PANELS_H * MAT_W * PANELS_W];
uint8_t nflare = 0;
uint32_t flare[maxflare];

/** pos - convert col/row to pixel position index. This takes into account
 *  the serpentine display, and mirroring the display so that 0,0 is the
 *  bottom left corner and (MAT_W-1,MAT_H-1) is upper right. You may need
 *  to jockey this around if your display is different.
 */
#ifndef MAT_LEFT
#define __MAT_RIGHT
#endif
#ifndef MAT_TOP
#define __MAT_BOTTOM
#endif
#if defined(MAT_COL_MAJOR)
const uint8_t phy_h = MAT_W;
const uint8_t phy_w = MAT_H;
#else
const uint8_t phy_h = MAT_H;
const uint8_t phy_w = MAT_W;
#endif
#if defined(MULTIPANEL)
uint16_t _pos( uint16_t col, uint16_t row ) {
#else
uint16_t pos( uint16_t col, uint16_t row ) {
#endif
#if defined(MAT_COL_MAJOR)
    uint16_t phy_x = xorg + (uint16_t) row;
    uint16_t phy_y = yorg + (uint16_t) col;
#else
    uint16_t phy_x = xorg + (uint16_t) col;
    uint16_t phy_y = yorg + (uint16_t) row;
#endif
#if defined(MAT_LEFT) && defined(MAT_ZIGZAG)
  if ( ( phy_y & 1 ) == 1 ) {
    phy_x = phy_w - phy_x - 1;
  }
#elif defined(__MAT_RIGHT) && defined(MAT_ZIGZAG)
  if ( ( phy_y & 1 ) == 0 ) {
    phy_x = phy_w - phy_x - 1;
  }
#elif defined(__MAT_RIGHT)
  phy_x = phy_w - phy_x - 1;
#endif
#if defined(MAT_TOP) and defined(MAT_COL_MAJOR)
  phy_x = phy_w - phy_x - 1;
#elif defined(MAT_TOP)
  phy_y = phy_h - phy_y - 1;
#endif
  return phy_x + phy_y * phy_w;
}

#if defined(MULTIPANEL)
uint16_t pos(uint16_t col, uint16_t row) {
#if defined(PANEL_TOP)
    uint16_t panel_y = PANELS_H - ( row / MAT_H ) - 1;
#else
    uint16_t panel_y = row / MAT_H;
#endif
    uint16_t panel_x = col / MAT_W;
#if defined(PANEL_ZIGZAG)
    if ( ( panel_y & 1 ) == 1 ) {
        panel_x = PANELS_W - panel_x - 1;
    }
#endif
    uint16_t pindex = panel_x + panel_y * PANELS_W;
    return MAT_W * MAT_H * pindex + _pos(col % MAT_W, row % MAT_H);
}
#endif

uint32_t isqrt(uint32_t n) {
  if ( n < 2 ) return n;
  uint32_t smallCandidate = isqrt(n >> 2) << 1;
  uint32_t largeCandidate = smallCandidate + 1;
  return (largeCandidate*largeCandidate > n) ? smallCandidate : largeCandidate;
}

// Set pixels to intensity around flare
void glow( int x, int y, int z ) {
  int b = z * 10 / flaredecay + 1;
  for ( int i=(y-b); i<(y+b); ++i ) {
    for ( int j=(x-b); j<(x+b); ++j ) {
      if ( i >=0 && j >= 0 && i < rows && j < cols ) {
        int d = ( flaredecay * isqrt((x-j)*(x-j) + (y-i)*(y-i)) + 5 ) / 10;
        uint8_t n = 0;
        if ( z > d ) n = z - d;
        if ( n > pix[i][j] ) { // can only get brighter
          pix[i][j] = n;
        }
      }
    }
  }
}

void newflare() {
  if ( nflare < maxflare && random(1,101) <= flarechance ) {
    int x = random(0, cols);
    int y = random(0, flarerows);
    int z = NCOLORS - 1;
    flare[nflare++] = (z<<16) | (y<<8) | (x&0xff);
    glow( x, y, z );
  }
}

unsigned long t = 0; /* keep time */

void make_fire() {
  uint16_t i, j;
  if ( t > millis() ) return;
  t = millis() + (1000 / FPS);

  // First, move all existing heat points up the display and fade
  for ( i=rows-1; i>0; --i ) {
    for ( j=0; j<cols; ++j ) {
      uint8_t n = 0;
      if ( pix[i-1][j] > 0 )
        n = pix[i-1][j] - 1;
      pix[i][j] = n;
    }
  }

  // Heat the bottom row
  for ( j=0; j<cols; ++j ) {
    i = pix[0][j];
    if ( i > 0 ) {
      pix[0][j] = random(NCOLORS-6, NCOLORS-2);
    }
  }

  // flare
  for ( i=0; i<nflare; ++i ) {
    int x = flare[i] & 0xff;
    int y = (flare[i] >> 8) & 0xff;
    int z = (flare[i] >> 16) & 0xff;
    glow( x, y, z );
    if ( z > 1 ) {
      flare[i] = (flare[i] & 0xffff) | ((z-1)<<16);
    } else {
      // This flare is out
      for ( int j=i+1; j<nflare; ++j ) {
        flare[j-1] = flare[j];
      }
      --nflare;
    }
  }
  newflare();

  // Set and draw
  for ( i=0; i<rows; ++i ) {
    for ( j=0; j<cols; ++j ) {
      matrix[pos(j,i)] = colorsRed[pix[i][j]];
    }
  }
  FastLED.show();
}
void newflareBlue() {
  if ( nflare < maxflare && random(1,101) <= flarechance ) {
    int x = random(0, cols);
    int y = random(0, flarerows);
    int z = BCOLORS - 1;
    flare[nflare++] = (z<<16) | (y<<8) | (x&0xff);
    glow( x, y, z );
  }
}

void make_fireBlue() {
  uint16_t i, j;
  if ( t > millis() ) return;
  t = millis() + (1000 / FPS);

  // First, move all existing heat points up the display and fade
  for ( i=rows-1; i>0; --i ) {
    for ( j=0; j<cols; ++j ) {
      uint8_t n = 0;
      if ( pix[i-1][j] > 0 )
        n = pix[i-1][j] - 1;
      pix[i][j] = n;
    }
  }

  // Heat the bottom row
  for ( j=0; j<cols; ++j ) {
    i = pix[0][j];
    if ( i > 0 ) {
      pix[0][j] = random(BCOLORS-6, BCOLORS-2);
    }
  }

  // flare
  for ( i=0; i<nflare; ++i ) {
    int x = flare[i] & 0xff;
    int y = (flare[i] >> 8) & 0xff;
    int z = (flare[i] >> 16) & 0xff;
    glow( x, y, z );
    if ( z > 1 ) {
      flare[i] = (flare[i] & 0xffff) | ((z-1)<<16);
    } else {
      // This flare is out
      for ( int j=i+1; j<nflare; ++j ) {
        flare[j-1] = flare[j];
      }
      --nflare;
    }
  }
  newflareBlue();

  // Set and draw
  for ( i=0; i<rows; ++i ) {
    for ( j=0; j<cols; ++j ) {
      matrix[pos(j,i)] = colorsBlue[pix[i][j]];
    }
  }
  FastLED.show();
}

//Buttons
const int patternSelect = 2;     // Pattern Select
int buttonPushCounter = 1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;
const int Thunderstorm = 4;
int thunderstormState = 0;
int lastthunderstormState = 0;

void setup() {
  //Serial.begin(9600);
  FastLED.addLeds<MAT_TYPE, MAT_PIN, GRB>(matrix, (MAT_H * PANELS_H * MAT_W * PANELS_W));
  FastLED.setBrightness(BRIGHT);
  FastLED.clear();
  FastLED.show();
  pinMode(patternSelect, INPUT);  // Pull-Down by resistor
  pinMode(Thunderstorm, INPUT);
  pinMode(colorPin, INPUT);
  delay(2000);
}

void loop() {

  buttonState = digitalRead(patternSelect);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      if (buttonPushCounter == 4) {
        buttonPushCounter = 1;
      }
    }else{}
  }

  lastButtonState = buttonState;// save the current state as the last state, for next time through the loop

thunderstormState = digitalRead(Thunderstorm);
 //Serial.print(Thunderstorm);
 //Serial.println(thunderstormState);
  if (thunderstormState != lastthunderstormState) {
    if (thunderstormState == HIGH) {
      buttonPushCounter = 2;
      }
    }else{}
    lastthunderstormState = thunderstormState;
 
 switch (buttonPushCounter) {
    case 1:
      buttonPushCounter == 1; {
        make_fire();
        delay(40);
        break;
      }
    case 2:
      buttonPushCounter == 2; {
        make_fireBlue();
        delay(40);
        break;
      }
    case 3:
      buttonPushCounter == 3; {
        color();
        break;
      }
 }
}

void color() {
  int mappedHue;
 mappedHue = map(analogRead(colorPin), 0, 1023, 0, 255);
  fill_solid( matrix, NUM_LEDS, CHSV(mappedHue, 255, 255));
    FastLED.show();
  }
