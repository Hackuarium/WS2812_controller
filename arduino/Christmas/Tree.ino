uint16_t treeCounter = 0;

// green chrismas tree

void updateTree() {
  treeCounter++;
  if ((treeCounter % 4) != 0) return; // slow down a little bit the update

  for (uint16_t led = 0; led < LED_COUNT; led++) {
    if (state[led] == 0) {
      colors[led] =  RGBColor(getIntensity(), 0, 0);
    } else {
      state[led]--;
    }
  }

  // executed 6 times per s
  for (uint8_t i = 0; i < getParameter(PARAM_INTENSITY); i++) {
    uint16_t led = random(0, LED_COUNT);
    state[led] = random(pow(2, 6 - getParameter(PARAM_SPEED)), pow(2, 6 - getParameter(PARAM_SPEED)) * 4); // how long it will stay on
    setFullIntensityColor(led);
  }
}
