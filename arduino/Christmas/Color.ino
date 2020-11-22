
uint8_t maxIntensity = 255;

uint8_t hsvChangeSpeed = 1;
uint8_t hsvRandom = 60;
uint16_t hsvStatus = 0;


void setCurrentColorModel(uint8_t colorModel) {
  setAndSaveParameter(PARAM_COLOR_MODEL, colorModel);
}


void copy(uint16_t from, uint16_t to) {
  if (colors[from].red > 0) colors[to].red = colors[from].red;
  if (colors[from].green > 0) colors[to].green = colors[from].green;
  if (colors[from].blue > 0) colors[to].blue = colors[from].blue;
}


void setColor(uint16_t led) {
  uint8_t colorModel = getParameter(PARAM_COLOR_MODEL);
  if (colorModel == 9) {
    hsvStatus = (hsvStatus + hsvChangeSpeed) % 360;
    uint16_t h = (hsvStatus + random(0, hsvRandom)) % 360;
    colors[led] = hsvToRGB(h, 255, 255);
    return;
  }
  if (colorModel == 8) {
    colorModel = random(1, 8);
  }
  if (colorModel & 2) colors[led].red = maxIntensity;
  if (colorModel & 1) colors[led].green = maxIntensity;
  if (colorModel & 4) colors[led].blue = maxIntensity;
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
