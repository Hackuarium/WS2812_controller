unsigned int waveCounter = 0;

// We will store in state if it is the head of the comet

void updateWave(byte inverted) {
  waveCounter++;
  if ((waveCounter % (24 - getParameter(PARAM_SPEED) * 4 + 1)) != 0) return;

  rgb_color nextColor = getColor(getParameter(PARAM_INTENSITY) * 4);
  for (byte line = 0; line < LINES; line++) {
    if ((line + inverted) % 2) { // line 1,3,5,7,...
      for (byte i = 1; i < LED_PER_LINE; i++) {
        int led = line * LED_PER_LINE + i;
        copy(led, led - 1);
      }
      colors[(line + 1) * LED_PER_LINE - 1].red = nextColor.red;
      colors[(line + 1) * LED_PER_LINE - 1].green = nextColor.green;
      colors[(line + 1) * LED_PER_LINE - 1].blue = nextColor.blue;
    } else { // line 0,2,4,6,...
      for (int i = LED_PER_LINE - 2; i >= 0 ; i--) {
        int led = line * LED_PER_LINE + i;
        copy(led, led + 1);
      }
      colors[line * LED_PER_LINE].red = nextColor.red;
      colors[line * LED_PER_LINE].green = nextColor.green;
      colors[line * LED_PER_LINE].blue = nextColor.blue;
    }
  }
}
