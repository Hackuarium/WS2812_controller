void resetState() {
  for (int i = 0; i < LED_COUNT; i++) {
    state[i] = 0;
  }
}

void black() {
  for (int i = 0; i < LED_COUNT; i++) {
    colors[i].red = 0;
    colors[i].green = 0;
    colors[i].blue = 0;
  }
}
