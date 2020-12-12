void resetState() {
  for (int i = 0; i < LED_COUNT; i++) {
    state[i] = 0;
  }
}

void black() {
  for (int i = 0; i < LED_COUNT; i++) {
    colors[i].r = 0;
    colors[i].g = 0;
    colors[i].b = 0;
  }
}
