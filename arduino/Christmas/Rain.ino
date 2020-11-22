

void updateRain() {
  for (int led = 0; led < LED_COUNT; led++) {
    decreaseColor(led, 10);
  }

  if (random(7 - getParameter(PARAM_INTENSITY)) != 0) return;

  int led = random(0, LED_COUNT);
  setColor(led);
}
