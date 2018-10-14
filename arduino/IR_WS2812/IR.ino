
byte MONITORING = 13;
byte monitValue = LOW;

#define BUTTON_POWER       12
#define BUTTON_UP          1
#define BUTTON_DOWN        33
#define BUTTON_SOUND       44
#define BUTTON_LEFT        34
#define BUTTON_RIGHT       2
#define BUTTON_AUTO        52

#define BUTTON44_ON       19562325
#define BUTTON44_OFF      19628373
#define BUTTON44_QUICK    22013269
#define BUTTON44_SLOW     21503317
#define BUTTON44_21       20606805
#define BUTTON44_22       20681045
#define BUTTON44_23       19691861
#define BUTTON44_24       19760981
#define BUTTON44_31       20080469
#define BUTTON44_32       20158805
#define BUTTON44_33       19165525
#define BUTTON44_34       19238741
#define BUTTON44_41       20291413
#define BUTTON44_42       20210005
#define BUTTON44_43       19106133
#define BUTTON44_44       19035989


long unsigned timeLast = 0;
boolean highBit = true;
boolean raising = true;

long unsigned irCode = 0;
long unsigned newIrCode = 0;
byte currentBit = 0;

void irInterrupt() {
  long unsigned timeCurrent = micros();

  monitValue = ! monitValue;
  digitalWrite(MONITORING, monitValue);

  if (timeCurrent - timeLast > 2000 || timeCurrent < timeLast) {
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
    if (highBit) {
      if (raising) {
        bitSet(newIrCode, currentBit);
      }
      else {
        bitClear(newIrCode, currentBit);
      }
      currentBit++;
      if (currentBit == REMOTE_BITS) {
        if (irCode != newIrCode) {
          irCode = newIrCode;
          eventIR(irCode);
        }
      }
    }
  }
  /*
    Serial.print(currentBit);
    Serial.print(" ");
    Serial.println(timeCurrent-timeLast);
  */
  timeLast = timeCurrent;
};


byte getIntensity() { // value from 0 to 7 should be converted to 31 to 255
  int intensity = (getParameter(PARAM_INTENSITY) + 1) * 32 - 1;
  return (getParameter(PARAM_INTENSITY) + 1) * 32 - 1;
}


void eventIR(unsigned long irCode) {
  irCode = irCode >> 7;
  Serial.println(irCode);
  switch (irCode) {

    case  BUTTON44_ON:
      setAndSaveParameter(PARAM_POWER, 1);
      break;
    case  BUTTON44_OFF:
      setAndSaveParameter(PARAM_POWER, 0);
      break;


    case BUTTON_POWER:
      if (getParameter(PARAM_POWER) == 0) {
        setAndSaveParameter(PARAM_POWER, 1);
      } else {
        setAndSaveParameter(PARAM_POWER, 0);
      }
      break;
    case BUTTON_UP:
      if (getParameter(PARAM_INTENSITY) < 7) {
        incrementAndSaveParameter(PARAM_INTENSITY);
      }
      break;
    case BUTTON_DOWN:
      if (getParameter(PARAM_INTENSITY) > 0) {
        decrementAndSaveParameter(PARAM_INTENSITY);
      }
      break;
    case BUTTON_SOUND:
      if (getParameter(PARAM_COLOR_MODEL) > 8) {
        setAndSaveParameter(PARAM_COLOR_MODEL, 0);
      }
      else {
        incrementAndSaveParameter(PARAM_COLOR_MODEL);
      }
      break;
    case BUTTON44_QUICK:
    case BUTTON_RIGHT:
      if (getParameter(PARAM_SPEED) < 6) {
        incrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON44_SLOW:
    case BUTTON_LEFT:
      if (getParameter(PARAM_SPEED) > 0) {
        decrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON_AUTO:
      if (getParameter(PARAM_CHANGE) > 5) {
        setAndSaveParameter(PARAM_CHANGE, 0);
      }
      else {
        incrementAndSaveParameter(PARAM_CHANGE);
      }
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}



void setupIR() {
  pinMode(1, INPUT);
  digitalWrite(1, HIGH);
  pinMode(MONITORING, OUTPUT);
  attachInterrupt(2, irInterrupt, CHANGE);
}








