

#define LED_PIN     5

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


