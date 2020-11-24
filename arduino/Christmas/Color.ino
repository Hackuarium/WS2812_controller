#define HSV_CHANGE_SPEED  1
#define MAX_INTENSITY     255
#define HSV_RANDOM        60

#define COLOR_ORANGE         1
#define COLOR_ORANGE_RANDOM  2
#define COLOR_CYAN           3
#define COLOR_CYAN_RANDOM    4
#define COLOR_VIOLET         5
#define COLOR_VIOLET_RANDOM  6


uint16_t hsvStatus = 0;

void setCurrentColorModel(uint8_t colorModel) {
  setAndSaveParameter(PARAM_COLOR_MODEL, colorModel);
}

void copy(uint16_t from, uint16_t to) {
  colors[to].red = colors[from].red;
  colors[to].green = colors[from].green;
  colors[to].blue = colors[from].blue;
}

// 1 to 7: rgb color
// 8 : one of the 7 colors
// 9 : hsl +- 60
// 10: hsl
// 11: hsl random

rgb_color getColor() {
  return getColor( getParameter(PARAM_COLOR_MODEL), HSV_CHANGE_SPEED);
}

rgb_color getColor(byte hsbChangeSpeed ) {
  return getColor( getParameter(PARAM_COLOR_MODEL), hsbChangeSpeed);
}

rgb_color getColor(byte colorModel, byte hsbChangeSpeed) {
  if (colorModel == 0) {
    return rgb_color(255, 255, 255);
  }
  if (colorModel == COLOR_ORANGE) {// moving red orange yellow
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 120;
    return hsvToRGB(0 + (hsvStatus < 60 ? hsvStatus : 119 - hsvStatus), 255, 255);
  }
  if (colorModel == COLOR_ORANGE_RANDOM) { // random red orange yellow
    return hsvToRGB(0 + random(0, 60), 255, 255);
  }
  if (colorModel == COLOR_CYAN) { // moving cyan bleu
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 120;
    return hsvToRGB(180 + (hsvStatus < 60 ? hsvStatus : 119 - hsvStatus), 255, 255);
  }
  if (colorModel == COLOR_CYAN_RANDOM) { // random cyan bleu
    return hsvToRGB(180 + random(0, 60), 255, 255);
  }
  if (colorModel == COLOR_VIOLET) { // moving blue violet
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 120;
    return hsvToRGB(240 + (hsvStatus < 60 ? hsvStatus : 119 - hsvStatus), 255, 255);
  }
  if (colorModel == COLOR_VIOLET_RANDOM) { // random blue violet
    return hsvToRGB(240 + random(0, 60), 255, 255);
  }
  if (colorModel == 7) {
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 360;
    uint16_t h = (hsvStatus + random(0, HSV_RANDOM)) % 360;
    return hsvToRGB(h, 255, 255);
  }
  if (colorModel == 8) {
    hsvStatus = (hsvStatus + hsbChangeSpeed) % 360;
    return hsvToRGB(hsvStatus, 255, 255);
  }
  if (colorModel == 9) {
    return hsvToRGB(random(0, 360), 255, 255);
  }

  /*
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    if (colorModel & 2) r = MAX_INTENSITY;
    if (colorModel & 1) g = MAX_INTENSITY;
    if (colorModel & 4) b = MAX_INTENSITY;
    return rgb_color(r, g, b);
  */

}

void setColor(uint16_t led) {
  colors[led] = getColor();
}

void decreaseColor(int led) {
  decreaseColor(led, 1);
}

void decreaseColor(uint16_t led, uint8_t increment) {
  if (colors[led].red > increment) {
    colors[led].red -= increment;
  } else {
    colors[led].red = 0;
  }
  if (colors[led].green > increment) {
    colors[led].green -= increment;
  } else {
    colors[led].green = 0;
  }
  if (colors[led].blue > increment) {
    colors[led].blue -= increment;
  } else {
    colors[led].blue = 0;
  }
}

/**
   h: hue (0-359)
   s: saturation (0-255)
   h: hue (0-255)
*/
rgb_color hsvToRGB(uint16_t h, uint8_t s, uint8_t v) {
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
  return rgb_color(r, g, b);
}

rgb_color getRandomRGBColor() {
  byte colorModel = random(1, 8);
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  if (colorModel & 2) r = MAX_INTENSITY;
  if (colorModel & 1) g = MAX_INTENSITY;
  if (colorModel & 4) b = MAX_INTENSITY;
  return rgb_color(r, g, b);
}
