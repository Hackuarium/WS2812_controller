uint16_t treeCounter = 0;

void updateTree() {
  treeCounter++;
  if ((treeCounter % (24 - getParameter(PARAM_SPEED) * 4 + 1)) != 0) return;

  for (uint16_t led = 0; led < LED_COUNT; led++) {
    if (state[led] == 0) {
      colors[led] =  rgb_color(getIntensity(), 0, 0);
    } else {
      state[led]--;
    }
  }

  uint16_t led = random(0, LED_COUNT);
  state[led] = random(getParameter(PARAM_INTENSITY), getParameter(PARAM_INTENSITY) * 4);
  setFullIntensityColor(led);

}
