uint16_t tinselCounter = 0;
uint16_t tinselState = 0;

void updateTinsel() {
  tinselCounter++;
  if ((tinselCounter % (24 - getParameter(PARAM_SPEED) * 4 + 1)) != 0) return;

  for (uint16_t led = 0; led < LED_COUNT; led++) {
    if (state[led] == 0) {
      colors[led] =  RGBColor(getIntensity(), 0, 0);
    } else {
      state[led]--;
    }
  }

  RGBColor color = getColor();

  for (byte width = 0; width < 3; width++) {
    byte line = 5;
    uint16_t led = line * tinselState++;
    state[led] = getParameter(PARAM_INTENSITY) * 4;
    setColor(led);
  }
}
