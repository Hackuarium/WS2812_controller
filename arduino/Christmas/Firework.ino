#define FIREWORK_DECREASE_SPEED 25

unsigned int fireworkCounter = 0;


// We will store in state if it is the head of the comet

void updateFirework() {
  fireworkCounter++;
  if ((fireworkCounter % (7 - getParameter(PARAM_SPEED))) == 0) {

    // we move the head
    for (byte line = 0; line < LINES; line++) {
      if ((line % 2) == 0) { // check the direction
        moveCometHeadUp(line);
      } else {
        moveCometHeadDown(line);
      }
      for (byte i = LED_PER_LINE - 3; i < LED_PER_LINE; i++) {
        int led = getLed(line, i);
        if (state[led]) {
          firework();
        }
      }
    }

    // we decreate the intensity of the firework
    for (int led = 0; led < LED_COUNT; led++) {
      if (! state[led]) {
        decreaseColor(led, FIREWORK_DECREASE_SPEED);
      }
    }
  }

  // we create a new firework
  if (random(16 - getParameter(PARAM_INTENSITY) * 2) != 0) return;
  int line = random(0, LINES);
  int led = getLed(line, 0, false);
  Serial.println(led);
  state[led] = 1;
  colors[led] = rgb_color(getIntensity(), getIntensity(), getIntensity());
}

void firework() {
  byte line = random(0, LINES);
  for (byte i = 0; i < 20; i++) {
    if (line % 2) {
      setFullIntensityColor(line * LED_PER_LINE + random(0, 6));
    } else {
      setFullIntensityColor((line + 1) * LED_PER_LINE - random(1, 7));
    }
  }
}
