
uint16_t getLed(byte line, byte position) {
  return getLed(line, position, false);
}

uint16_t getLed(byte line, byte position, boolean inverted) {
  uint16_t led = line * LED_PER_LINE;
  if ((line + inverted) % 2 == 0) {
    return led + position;
  } else {
    return led + (LED_PER_LINE - 1) - position;
  }
}
