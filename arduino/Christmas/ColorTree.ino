
uint16_t colorTreeCounter = 0;

void updateColorTree() {

  colorTreeCounter++;

  // this is called 25 times per second

  // we check if we need to put a new led
  for (uint16_t led = 0; led < LED_COUNT; led++) {
    if (state[led] != 0) {
      state[led]--;
      if (state[led] == 0) {
        setColor(led);
      }
    }
  }

  // we change color from 0 to LED_COUNT per second pased on PARAM_SPEED (from 0 to 6)
  uint16_t ledsToChange = random(0, LED_COUNT / 25 / getParameter(PARAM_SPEED)) * getParameter(PARAM_SPEED);
  for (uint16_t led = 0; led < ledsToChange; led++) {
    if (state[led] == 0) {
      setColor(led);
    }
  }

  if (colorTreeCounter % random(0, 7 - getParameter(PARAM_SPEED)) == 0) {
    uint16_t led = random(0, LED_COUNT);
    state[led] = random(getParameter(PARAM_INTENSITY), getParameter(PARAM_INTENSITY) * 4) * 5 + 5;
    setFullIntensityColor(led);
  }
}
