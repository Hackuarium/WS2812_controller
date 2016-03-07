#include <FastLED.h>

#define LED_PIN     8
#define NUM_LEDS    20
#define BRIGHTNESS  20
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 3


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

  if (counter % 7 == 0) {
    red=random(0,255);
    green=random(0,255);
    blue=random(0,255);
    counter=0;
  }
  counter++;

  current=(current+1) % NUM_LEDS;
  next=(current+1) % NUM_LEDS;

  leds[current].red=red;
  leds[current].green=green;
  leds[current].blue=blue;

  leds[next].red=0;
  leds[next].green=0;
  leds[next].blue=0;


  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


