

#define LED_PIN     6   // 6 : internal, 5: external
#define REMOTE_BITS 32  // 32 for 44 button remote, otherwise 13 for 7 buttons remote
#define NUM_LEDS    3


void setup() {
  Serial.begin(115200);
  setupParameters();
  setupIR();
  setupFastLED();

}

void loop() {
  loopFastLED();
  delay(50);



}


