#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    20
#define BRIGHTNESS  20
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 2


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

int current=0;
int next=0;
byte counter=0;
byte red, green, blue;

void loop()
{

  if (counter % 6 == 0) {
    red=255;
    green=0;
    blue=0;
    counter=0;
  }
  if (counter % 6 == 1) {
    red=255;
    green=100;
    blue=0;
  }
  if (counter % 6 == 2) {
    red=200;
    green=255;
    blue=0;
    }
  if (counter % 6 == 3) {
    red=0;
    green=255;
    blue=0;
  }
  if (counter % 6 == 4) {
    red=0;
    green=0;
    blue=255;
  }
  if (counter % 6 == 5) {
    red=200;
    green=0;
    blue=255;
  }
 
  counter++;



  leds[current].red=red;
  leds[current].green=green;
  leds[current].blue=blue;

  leds[next].red=0;
  leds[next].green=0;
  leds[next].blue=0;

  current=(current+1) % NUM_LEDS;
  next=(current+1) % NUM_LEDS;

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


