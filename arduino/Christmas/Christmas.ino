#include "./PololuLedStrip.h"

#define LED_PIN     5  // 6 : internal, 5: external

#define LINES         8
#define LED_PER_LINE  25
#define LED_COUNT     LINES * LED_PER_LINE

#define REMOTE_BITS 13

PololuLedStrip<LED_PIN> ledStrip;

rgb_color colors[LED_COUNT];

byte state[LED_COUNT];

byte currentBit = 0;

void setup() {
  Serial.begin(115200);
  setupParameters();
  setupIR();
  resetState();



}

unsigned long lastRun = 0;

void loop() {
  // max 25 per seconds
  if (currentBit > 1) {
    delay(200);
    currentBit=0;
  }
  if ((millis() - lastRun) >= 25) {
    lastRun = millis();
    update();
    ledStrip.write(colors, LED_COUNT);
  }
}

void clearState() {
  for (byte i = 0; i < 50; i++) {
    state[i] = 0;
  }
}
