#define COMET_DECREASE_SPEED 25

unsigned int cometCounter = 0;


// We will store in state if it is the head of the comet

void updateComet(byte inverted) {
  cometCounter++;
  if ((cometCounter % (7 - getParameter(PARAM_SPEED))) == 0) {
    // we move the head of the comet
    for (byte line = 0; line < LINES; line++) {
      if (line % 2) { // check the direction
        for (byte i = 0; i < LED_PER_LINE; i++) {
          int led = (line + inverted) % LINES * LED_PER_LINE + i;
          if (state[led]) { // need to turn on the next one full power
            state[led] = 0;
            if (i > 0) {
              state[led - 1] = 1;
              copy(led, led - 1);
            }
          }
        }
      } else {
        for (int i = LED_PER_LINE - 1; i >= 0 ; i--) {
          int led = (line + inverted) % LINES * LED_PER_LINE + i;
          if (state[led]) { // need to turn on the next one full power
            state[led] = 0;
            if (i < LED_PER_LINE - 1) {
              state[led + 1] = 1;
              copy(led, led + 1);
            }
          }
        }
      }
    }

    // we decreate the intensity of the coment
    for (int led = 0; led < LED_COUNT; led++) {
      if (! state[led]) {
        decreaseColor(led, COMET_DECREASE_SPEED);
      }
    }
  }

  // we create a new comet
  if (random(16 - getParameter(PARAM_INTENSITY) * 2) != 0) return;
  int line = random(0, LINES);
  int led = line * LED_PER_LINE + (line % 2) * (LED_PER_LINE - 1);
  state[led] = 1;
  setColor(led);
}
