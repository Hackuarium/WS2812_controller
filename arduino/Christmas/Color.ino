#define HSV_RANDOM        60

#define COLOR_ORANGE         1
#define COLOR_ORANGE_RANDOM  2
#define COLOR_GREEN          3
#define COLOR_GREEN_RANDOM   4
#define COLOR_VIOLET         5
#define COLOR_VIOLET_RANDOM  6
#define COLOR_RAINBOW        7
#define COLOR_RAINBOW_RANDOM 8
#define COLOR_FULL_RANDOM    9

uint16_t hsvStatus = 0;

void setCurrentColorModel(uint8_t colorModel) {
  setAndSaveParameter(PARAM_COLOR_MODEL, colorModel);
}

void copy(uint16_t from, uint16_t to) {
  colors[to].r = colors[from].r;
  colors[to].g = colors[from].g;
  colors[to].b = colors[from].b;
}


byte getHSVSpeedChange() {
  if (getParameter(PARAM_COLOR_CHANGE_SPEED) >= 3) {
    return pow(2, getParameter(PARAM_COLOR_CHANGE_SPEED) - 3);
  } else {
    return random(0, pow(4, 3 - getParameter(PARAM_COLOR_CHANGE_SPEED))) == 0;
  }
}

// 1 to 7: rgb color
// 8 : one of the 7 colors
// 9 : hsl +- 60
// 10: hsl
// 11: hsl random

RGBColor getColor() {
  return getColor( getParameter(PARAM_COLOR_MODEL), getHSVSpeedChange());
}

RGBColor getColor(byte hsbChangeSpeed ) {
  return getColor( getParameter(PARAM_COLOR_MODEL), hsbChangeSpeed);
}

RGBColor getColor(byte colorModel, byte hsbChangeSpeed) {
  return getColor(colorModel,  hsbChangeSpeed, getIntensity());
}

RGBColor getColor(byte colorModel, byte hsbChangeSpeed, byte intensity) {
  if (colorModel == 0) {
    return RGBColor(255, 255, 255);
  }
  if (colorModel == COLOR_ORANGE) {// moving red orange yellow
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 120;
    return hsvToRGB(0 + (hsvStatus < 60 ? hsvStatus : 119 - hsvStatus), 255, intensity);
  }
  if (colorModel == COLOR_ORANGE_RANDOM) { // random red orange yellow
    return hsvToRGB(0 + random(0, 60), 255, intensity);
  }
  if (colorModel == COLOR_GREEN) {
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 120;
    return hsvToRGB(90 + (hsvStatus < 60 ? hsvStatus : 119 - hsvStatus), 255, intensity);
  }
  if (colorModel == COLOR_GREEN_RANDOM) {
    return hsvToRGB(90 + random(0, 60), 255, intensity);
  }
  if (colorModel == COLOR_VIOLET) { // moving blue violet
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 240;
    return hsvToRGB(240 + (hsvStatus < 120 ? hsvStatus : 239 - hsvStatus), 255, intensity);
  }
  if (colorModel == COLOR_VIOLET_RANDOM) { // random blue violet
    return hsvToRGB(240 + random(0, 120), 255, intensity);
  }
  if (colorModel == COLOR_RAINBOW_RANDOM) {
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 360;
    uint16_t h = (hsvStatus + random(0, HSV_RANDOM)) % 360;
    return hsvToRGB(h, 255, intensity);
  }
  if (colorModel == COLOR_RAINBOW) {
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 360;
    return hsvToRGB(hsvStatus, 255, intensity);
  }
  if (colorModel == COLOR_FULL_RANDOM) {
    return hsvToRGB(random(0, 360), 255, intensity);
  }

  /*
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    if (colorModel & 2) r = MAX_INTENSITY;
    if (colorModel & 1) g = MAX_INTENSITY;
    if (colorModel & 4) b = MAX_INTENSITY;
    return RGBColor(r, g, b);
  */

}

void setColor(uint16_t led) {
  colors[led] = getColor();
}

void setFullIntensityColor(uint16_t led) {
  colors[led] = getColor( getParameter(PARAM_COLOR_MODEL), getHSVSpeedChange(), 255);
}

void decreaseColor(int led) {
  uint8_t increment = 0;
  if (getParameter(PARAM_COLOR_DECREASE_SPEED) >= 2) {
    increment = pow(3, getParameter(PARAM_COLOR_DECREASE_SPEED) - 2);
  } else {
    increment = random(0, pow(2, 2 - getParameter(PARAM_COLOR_DECREASE_SPEED))) == 0;
  }
  decreaseColor(led, increment);
}

void decreaseColor(uint16_t led, uint8_t increment) {
  if (getParameter(PARAM_COLOR_DECREASE_MODEL) == 0) {
    if (colors[led].r > increment) {
      colors[led].r -= increment;
    } else {
      colors[led].r = 0;
    }
    if (colors[led].g > increment) {
      colors[led].g -= increment;
    } else {
      colors[led].g = 0;
    }
    if (colors[led].b > increment) {
      colors[led].b -= increment;
    } else {
      colors[led].b = 0;
    }
  } else { // decrease in HSV model
    HSVColor hsv = rgbToHSV(colors[led]);
    if (hsv.v > increment) {
      hsv.v-=increment;
      colors[led] = hsvToRGB(hsv);
    } else {
      colors[led] = RGBColor(0,0,0);
    }
  }
}

/**
   h: hue (0-359)
   s: saturation (0-255)
   h: hue (0-255)
*/
RGBColor hsvToRGB(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return RGBColor(g, r, b);
}

RGBColor hsvToRGB(HSVColor hsv) {
  return hsvToRGB(hsv.h, hsv.s, hsv.v);
}


HSVColor rgbToHSV(RGBColor rgb) {
  HSVColor hsv;

  uint8_t rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
  uint8_t rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

  hsv.v = rgbMax;
  if (hsv.v == 0) {
    hsv.h = 0;
    hsv.s = 0;
    return hsv;
  }

  hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
  if (hsv.s == 0) {
    hsv.h = 0;
    return hsv;
  }

  if (rgbMax == rgb.r)
    hsv.h = 0 + 60 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
  else if (rgbMax == rgb.g)
    hsv.h = 120 + 60 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
  else
    hsv.h = 240 + 60 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

  return hsv;
}


RGBColor getRandomRGBColor() {
  byte colorModel = random(1, 8);
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  if (colorModel & 2) r = getIntensity();
  if (colorModel & 1) g = getIntensity();
  if (colorModel & 4) b = getIntensity();
  return RGBColor(r, g, b);
}

byte getIntensity() {
  switch (getParameter(PARAM_POWER)) {
    case 0:
      return 0;
    case 1:
      return 20;
    case 2:
      return 70;
    default:
      return 255;
  }
}
