

void updateRain() {
  for (int led = 0; led < LED_COUNT; led++) {
    decreaseColor(led, getParameter(PARAM_SPEED));
  }

  byte nbEvents = 1;
  if (getParameter(PARAM_INTENSITY) >= 3) {
    nbEvents = pow(2, getParameter(PARAM_INTENSITY) - 3);
  } else {
    return random(0, pow(2, 2 - getParameter(PARAM_INTENSITY))) != 0;
  }


  for (byte i = 0; i < nbEvents; i++) {
    int led = random(0, LED_COUNT);
    setColor(led);
  }


}
