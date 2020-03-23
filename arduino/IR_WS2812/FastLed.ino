#include <FastLED.h>

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;


extern const TProgmemPalette16 pinksBlackPalette PROGMEM;
extern const TProgmemPalette16 blackPalette PROGMEM;
extern const TProgmemPalette16 blueRedPalette PROGMEM;
extern const TProgmemPalette16 blueGreenRedPalette PROGMEM;
extern const TProgmemPalette16 blueDarkVioletPalette PROGMEM;
extern const TProgmemPalette16 orangeBluePalette PROGMEM;
extern const TProgmemPalette16 mixedColorsPalette PROGMEM;

void setupFastLED() {
  //  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND; // could also be NOBLEND
}


void loopFastLED() {
  FastLED.setBrightness(  getIntensity() );

  if (getParameter(PARAM_POWER) == 0) {
    currentPalette = blackPalette;
  } else {
    if (getParameter(PARAM_AUTO_MODE_CHANGE) == 1 && counter == 100) {
      if (getParameter(PARAM_COLOR_MODEL) < 21) {
        incrementParameter(PARAM_COLOR_MODEL);
      } else {
        setParameter(PARAM_COLOR_MODEL, -1);
      }
      counter = 0;
    }
    getPalette();
  }
  static uint8_t startIndex = 0;
  startIndex = startIndex + getParameter(PARAM_SPEED); /* motion speed */
  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
    colorIndex += getParameter(PARAM_CHANGE); // number of 'waves'
  }
}

// RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
void getPalette() {
  switch (getParameter(PARAM_COLOR_MODEL)) {
    case -1:
      setupManualPalette();
      break;
    case 0:
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 1:
      currentPalette = RainbowStripeColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 2:
      currentPalette = OceanColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 3:
      currentPalette = pinksBlackPalette;
      currentBlending = NOBLEND;
      break;
    case 4:
      currentPalette = LavaColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 5:
      currentPalette = ForestColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 6:
      currentPalette = PartyColors_p;
      currentBlending = LINEARBLEND;
      break;
    case 7:
      currentPalette = blueRedPalette;
      currentBlending = LINEARBLEND;
      break;
    case 8:
      currentPalette = blueGreenRedPalette;
      currentBlending = LINEARBLEND;
      break;
    case 9:
      currentPalette = blueDarkVioletPalette;
      currentBlending = LINEARBLEND;
      break;
    case 10:
      setupRandomPalette();
      currentBlending = NOBLEND;
      break;
    case 11:
      setupBlackAndWhiteStripedPalette();
      currentBlending = NOBLEND;
      break;
    case 12:
      setupRedPalette();
      break;
    case 13:
      setupGreenPalette();
      break;
    case 14:
      setupBluePalette();
      break;
    case 15:
      setupWhitePalette();
      break;
    case 16:
      setupPurpleAndGreenPalette();
      currentBlending = LINEARBLEND;
      break;
    case 17:
      setupWhiteRandomPalette();
      currentBlending = NOBLEND;
      break;
    case 18:
      currentPalette = orangeBluePalette;
      currentBlending = LINEARBLEND;
      break;
    case 19:
      currentPalette = mixedColorsPalette;
      currentBlending = NOBLEND;
      break;
    case 20:
      setupWarmWhitePalette();
      currentBlending = LINEARBLEND;
      break;
    case 21:
      setupNeonPalette();
      currentBlending = LINEARBLEND;
      break;         
  }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.


// This function fills the palette with manually defined intensities for R, G and B.
void setupManualPalette() {
  byte red = getParameter(PARAM_RED_INTENSITY) * 36  ;
  byte green = getParameter(PARAM_GREEN_INTENSITY) * 36;
  byte blue = getParameter(PARAM_BLUE_INTENSITY) * 36;

  for ( byte i = 0; i < 16; i++) {
    currentPalette[i] = CRGB(red, green, blue);
  }
}

// This function fills the palette with white.
void setupWhitePalette() {
  for ( byte i = 0; i < 16; i++) {
    currentPalette[i] = CRGB(255, 255, 255);
  }
}

// This function fills the palette with red.
void setupRedPalette() {
  for ( byte i = 0; i < 16; i++) {
    currentPalette[i] = CRGB(255, 0, 0);
  }
}

// This function fills the palette with green.
void setupGreenPalette() {
  for ( byte i = 0; i < 16; i++) {
    currentPalette[i] = CRGB(0, 255, 0);
  }
}

// This function fills the palette with blue.
void setupBluePalette() {
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CRGB(0, 0, 255);
  }
}

// This function fills the palette with random colors and intensities.
void setupRandomPalette()
{
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV(random8(), 255, random8());
  }
}

// This function fills the palette with random intensities of white.
void setupWhiteRandomPalette()
{
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV(255, 0, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void setupBlackAndWhiteStripedPalette() {
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void setupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 pinksBlackPalette PROGMEM =
{
  CRGB::DarkOrchid,
  CRGB::Black,
  CRGB::Tomato,
  CRGB::Black,
  CRGB::HotPink,
  CRGB::Black,
  CRGB::Crimson,
  CRGB::Black,
  CRGB::MediumVioletRed,
  CRGB::Black,
  CRGB::Coral,
  CRGB::Black,
  CRGB::Amethyst,
  CRGB::Black,
  CRGB::Fuchsia,
  CRGB::Black
};


const TProgmemPalette16 blackPalette PROGMEM =
{
  CRGB::Black,
  CRGB::Black, 
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};


const TProgmemPalette16 blueRedPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red
};

const TProgmemPalette16 blueGreenRedPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, 
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Green,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red,
  CRGB::Red
};

const TProgmemPalette16 blueDarkVioletPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, 
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet,
  CRGB::DarkViolet
};

const TProgmemPalette16 orangeBluePalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Blue, 
  CRGB::Green,
  CRGB::Green,
  CRGB::Yellow,
  CRGB::Yellow,
  CRGB::Orange,
  CRGB::Orange,
  CRGB::Orange,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Blue
};

const TProgmemPalette16 mixedColorsPalette PROGMEM =
{
  CRGB::Blue,
  CRGB::Yellow, 
  CRGB::Red,
  CRGB::Green,
  CRGB::Purple,
  CRGB::Orange,
  CRGB::Purple,
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Yellow,
  CRGB::Orange,
  CRGB::Blue,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Purple
};

// This function sets up a palette of warm white shades.
void setupWarmWhitePalette()
{
  CRGB warmWhite = CHSV(50, 100, 255);
  CRGB yellow    = CHSV(45, 130, 255);
  CRGB orange    = CHSV(50, 140, 255);

  currentPalette = CRGBPalette16(
                     warmWhite,  warmWhite,  warmWhite,  yellow,
                     yellow, yellow, orange,  orange,
                     orange,  orange,  yellow,  yellow,
                     yellow, warmWhite, warmWhite,  warmWhite );
}

// This function sets up a palette of warm white shades.
void setupNeonPalette()
{
  CRGB orange   = CHSV(40, 255, 255);
  CRGB yellow   = CHSV(70, 255, 255);
  CRGB green    = CHSV(100, 255, 255);

  currentPalette = CRGBPalette16(
                     green,  green,  green,  yellow,
                     yellow, yellow, orange,  orange,
                     orange,  orange,  orange,  yellow,
                     yellow, yellow, green,  green );
}


