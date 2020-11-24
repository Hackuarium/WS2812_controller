

void updateRain() {
  for (int led = 0; led < LED_COUNT; led++) {
    decreaseColor(led, getParameter(PARAM_SPEED));
  }

  if (random(8 - getParameter(PARAM_INTENSITY)) != 0) return;

  int led = random(0, LED_COUNT);
  setColor(led);
}
