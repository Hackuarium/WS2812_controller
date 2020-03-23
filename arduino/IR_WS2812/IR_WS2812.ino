

#define LED_PIN     5   // 6 : internal, 5: external
#define REMOTE_BITS 13  // 32 for 44 button remote, otherwise 13 for 7 buttons remote
#define NUM_LEDS    400
#define AUTOCHANGE_VALUE 100


void setup() {
  Serial.begin(115200);
  setupParameters();
  setupIR();
  setupFastLED();

}

byte currentBit = 0;

void loop() {

  autoMode();

  loopFastLED();
  delay(50);
  /*
      It seems that FastLED blocs the interrupts so no IR remote control info
      if we receive some remote control instruction we need to wait a little bit
  */
  if (currentBit > 1) {
    delay(200); 
  }

}
