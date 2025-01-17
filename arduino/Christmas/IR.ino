
byte MONITORING = 13;
byte monitValue = LOW;


#define BUTTON_POWER       12
#define BUTTON_UP          1
#define BUTTON_DOWN        33
#define BUTTON_SOUND       44
#define BUTTON_LEFT        34
#define BUTTON_RIGHT       2
#define BUTTON_AUTO        52


long unsigned timeLast = 0;
boolean highBit = true;
boolean raising = true;

long unsigned irCode = 0;
long unsigned newIrCode = 0;


void irInterrupt() {
  long unsigned timeCurrent = micros();

  monitValue = ! monitValue;
  digitalWrite(MONITORING, monitValue);

  if (timeCurrent - timeLast > 2000 || timeCurrent < timeLast) {
    currentBit = 0;
    newIrCode = 0;
    highBit = true;
    raising = true;
  } else {
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

void eventIR(unsigned long irCode) {
  setAndSaveParameter(PARAM_AUTO_MODE_CHANGE, 0);
  irCode = irCode >> 7;
  if ( getParameter(PARAM_POWER) == 0) {
    setParameter(PARAM_SPECIAL_CONFIG, 100); // 4 seconds to display the current configuration while being off
  }
  switch (irCode) {
    case BUTTON_POWER:
      if (getParameter(PARAM_POWER) > 2) {
        setAndSaveParameter(PARAM_POWER, 0);
      } else {
        incrementAndSaveParameter(PARAM_POWER);
      }
      break;

    case BUTTON_UP:
      if (getParameter(PARAM_POWER) > 0) {
        if (getParameter(PARAM_INTENSITY) < 7) {
          incrementAndSaveParameter(PARAM_INTENSITY);
        }
      } else {
        if (getParameter(PARAM_COLOR_DECREASE_SPEED) < 6) {
          incrementAndSaveParameter(PARAM_COLOR_DECREASE_SPEED);
        }
      }
      break;
    case BUTTON_DOWN:
      if (getParameter(PARAM_POWER) > 0) {
        if (getParameter(PARAM_INTENSITY) > 0) {
          decrementAndSaveParameter(PARAM_INTENSITY);
        }
      } else {
        if (getParameter(PARAM_COLOR_DECREASE_SPEED) > 0) {
          decrementAndSaveParameter(PARAM_COLOR_DECREASE_SPEED);
        }
      }
      break;

    case BUTTON_SOUND: // color model
      if (getParameter(PARAM_POWER) > 0) {
        if (getParameter(PARAM_COLOR_MODEL) > 8) {
          setAndSaveParameter(PARAM_COLOR_MODEL, 0);
        }
        else {
          incrementAndSaveParameter(PARAM_COLOR_MODEL);
        }
      } else {
        if (getParameter(PARAM_COLOR_DECREASE_MODEL) == 0) {
          setParameter(PARAM_COLOR_DECREASE_MODEL, 1);
        } else {
          setParameter(PARAM_COLOR_DECREASE_MODEL, 0);
        }
      }
      break;
    case BUTTON_RIGHT:
      if (getParameter(PARAM_POWER) > 0) {
        if (getParameter(PARAM_SPEED) < 6) {
          incrementAndSaveParameter(PARAM_SPEED);
        }
      } else {
        if (getParameter(PARAM_COLOR_CHANGE_SPEED) < 6) {
          incrementAndSaveParameter(PARAM_COLOR_CHANGE_SPEED);
        }
      }

      break;
    case BUTTON_LEFT:
      if (getParameter(PARAM_POWER) > 0) {
        if (getParameter(PARAM_SPEED) > 0) {
          decrementAndSaveParameter(PARAM_SPEED);
        }
      } else {
        if (getParameter(PARAM_COLOR_CHANGE_SPEED) > 0) {
          decrementAndSaveParameter(PARAM_COLOR_CHANGE_SPEED);
        }
      }
      break;
    case BUTTON_AUTO: // change of program
      resetState();
      if (getParameter(PARAM_CURRENT_PROGRAM) > 6) {
        setAndSaveParameter(PARAM_CURRENT_PROGRAM, 0);
      }
      else {
        incrementAndSaveParameter(PARAM_CURRENT_PROGRAM);
      }
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
  printParameters();
}

void setupIR() {
  pinMode(1, INPUT);
  digitalWrite(1, HIGH);
  pinMode(MONITORING, OUTPUT);
  attachInterrupt(2, irInterrupt, CHANGE);
}
