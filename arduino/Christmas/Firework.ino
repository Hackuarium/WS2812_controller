#define FIREWORK_DECREASE_SPEED 25

unsigned int fireworkCounter = 0;


// We will store in state if it is the head of the comet

void updateFirework() {
  fireworkCounter++;
  if ((fireworkCounter % (7 - getParameter(PARAM_SPEED))) == 0) {
    // we move the head of the comet
    for (byte line = 0; line < LINES; line++) {
      if (line % 2) { // check the direction
        for (byte i = 0; i < LED_PER_LINE; i++) {
          int led = line * LED_PER_LINE + i;
          if (state[led]) { // need to turn on the next one full power
            state[led] = 0;
            if (i > 0) {
              state[led - 1] = 1;
              copy(led, led - 1);
            }
            if (i < 2) { // firework
              firework();
            }
          }
        }
      } else {
        for (int i = LED_PER_LINE - 1; i >= 0 ; i--) {
          int led = line * LED_PER_LINE + i;
          if (state[led]) { // need to turn on the next one full power
            state[led] = 0;
            if (i < LED_PER_LINE - 1) {
              state[led + 1] = 1;
              copy(led, led + 1);
            }
            if (i > (LED_PER_LINE - 3)) { // firework
              firework();
            }
          }
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
  int led = line * LED_PER_LINE + (line % 2) * (LED_PER_LINE - 1);
  state[led] = 1;
  colors[led]=rgb_color(255, 255, 255);
}

void firework() {
  byte line = random(0, LINES);
  for (byte i = 0; i < 20; i++) {
    if (line % 2) {
      setColor(line * LED_PER_LINE + random(0, 6));
    } else {
      setColor((line + 1) * LED_PER_LINE - random(1, 7));
    }
  }
}
