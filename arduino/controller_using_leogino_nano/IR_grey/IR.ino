
byte MONITORING = 13;
byte monitValue = HIGH;

#define BUTTON_POWER       0   // set to one if something is detected
#define BUTTON_UP          1
#define BUTTON_DOWN        2
#define BUTTON_SOUND       3
#define BUTTON_LEFT        4 // we are able to play a random sound between FIRST and LAST
#define BUTTON_RIGHT       5
#define BUTTON_AUTO        6

long unsigned timeLast = 0;
boolean highBit = true;
boolean raising = true;


int currentBit = 0;

byte buttons[7] = {
  12, 1, 33, 44, 34, 2, 52
};

void irInterrupt() {
  long unsigned timeCurrent = micros();

  monitValue = ! monitValue;
  digitalWrite(MONITORING, monitValue);

  if (timeCurrent - timeLast > 2000 || timeCurrent < timeLast) {
    timeLast = timeCurrent;
    currentBit = 0;
    newIrCode = 0;
    highBit = true;
    raising = true;
  }
  else {
    if (timeCurrent - timeLast < 1200) {
      highBit = !highBit;
    }
    raising = !raising;
    timeLast = timeCurrent;
    if (highBit) {
      if (raising) {
        bitSet(newIrCode, currentBit);
      }
      else {
        bitClear(newIrCode, currentBit);
      }
      currentBit++;
      if (currentBit == 13) {
        if (irCode != newIrCode) {
          irCode = newIrCode;
          eventIR(irCode);
        }
      }
    }
  }
};


void eventIR(int irCode) {
  irCode = irCode >> 7;

  setParameter(PARAM_LAST_KEY, irCode);

  for (byte i = 0; i < sizeof(buttons); i++) {
    if (irCode == buttons[i]) {
      switch (i) {
        case BUTTON_POWER:
          if (getParameter(PARAM_POWER) == 0) {
            setAndSaveParameter(PARAM_POWER, 1);
          } else {
            setAndSaveParameter(PARAM_POWER, 0);
          }
          break;
        case BUTTON_UP:
          incrementAndSaveParameter(PARAM_GREY1, 32, 255);
          break;
        case BUTTON_DOWN:
          decrementAndSaveParameter(PARAM_GREY1, 32, 0);
          break;
        case BUTTON_SOUND:
          setAndSaveParameter(PARAM_GREY1, 255);
          setAndSaveParameter(PARAM_GREY2, 255);
          break;
        case BUTTON_RIGHT:
          incrementAndSaveParameter(PARAM_GREY2, 32, 255);
          break;
        case BUTTON_LEFT:
          decrementAndSaveParameter(PARAM_GREY2, 32, 0);
          break;
        case BUTTON_AUTO:
          setAndSaveParameter(PARAM_GREY1, 127);
          setAndSaveParameter(PARAM_GREY2, 127);
          break;
        default:
          // if nothing else matches, do the default
          // default is optional
          break;
      }

      /*
            Serial.print(i);
            Serial.print(" - ");
            Serial.print(irCode,BIN);
            Serial.print(" - ");
            Serial.println(irCode);
      */
    }
  }
}


void setupIR() {
  pinMode(1, INPUT);
  digitalWrite(1, LOW);
  pinMode(MONITORING, OUTPUT);
  attachInterrupt(3, irInterrupt, CHANGE);

}













