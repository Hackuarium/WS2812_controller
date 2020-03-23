
byte MONITORING = 13;
byte monitValue = LOW;

#define BUTTON_POWER       12
#define BUTTON_UP          1
#define BUTTON_DOWN        33
#define BUTTON_SOUND       44
#define BUTTON_LEFT        34
#define BUTTON_RIGHT       2
#define BUTTON_AUTO        52

#if REMOTE_BITS == 32
#define BUTTON44  1

#define BUTTON44_BRIGHTER 20813653
#define BUTTON44_DIMMER   20736341
#define BUTTON44_ON_OFF   19562325
#define BUTTON44_PLAY     19628373

#define BUTTON44_R       20606805
#define BUTTON44_G       20681045
#define BUTTON44_B       19691861
#define BUTTON44_W       19760981

#define BUTTON44_31       20080469
#define BUTTON44_32       20158805
#define BUTTON44_33       19165525
#define BUTTON44_34       19238741

#define BUTTON44_41       20291413
#define BUTTON44_42       20210005
#define BUTTON44_43       19106133
#define BUTTON44_44       19035989

#define BUTTON44_51       21108565
#define BUTTON44_52       21227861
#define BUTTON44_53       21097301
#define BUTTON44_54       20976981

#define BUTTON44_61       21360469
#define BUTTON44_62       21238101
#define BUTTON44_63       21369685
#define BUTTON44_64       21491029

#define BUTTON44_RED_UP     21882709
#define BUTTON44_RED_DOWN   21634901
#define BUTTON44_BLUE_UP    21896021
#define BUTTON44_BLUE_DOWN  21619541
#define BUTTON44_GREEN_UP   21764437
#define BUTTON44_GREEN_DOWN 21750101

#define BUTTON44_QUICK    22013269
#define BUTTON44_SLOW     21503317
#define BUTTON44_AUTO     23065941
#define BUTTON44_FLASH    22547797
#define BUTTON44_FADE7    22021461

#define BUTTON44_JUMP3     22153045 // previous mode
#define BUTTON44_JUMP7     22280533 // next mode

#endif

// outdated

#if REMOTE_BITS == 22
#define BUTTON44  1
#define BUTTON44_DIMMER   22350
#define BUTTON44_DIMMER2  5973
#define BUTTON44_BRIGHTER 21840
#define BUTTON44_BRIGHTER2 26965
#define BUTTON44_OFF      341
#define BUTTON44_ON       32597
#define BUTTON44_21       28501
#define BUTTON44_22       4437
#define BUTTON44_23       31061
#define BUTTON44_24       1877
#define BUTTON44_31       26453
#define BUTTON44_32       6485
#define BUTTON44_33       29013
#define BUTTON44_34       3925
#define BUTTON44_41       8021
#define BUTTON44_42       24917
#define BUTTON44_43       2389
#define BUTTON44_44       30549
#define BUTTON44_QUICK    25941
#define BUTTON44_SLOW     7509
#endif

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
#ifdef BUTTON44
          eventIR44(irCode);
#else
          eventIR(irCode);
#endif
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
  setAndSaveParameter(PARAM_AUTO_MODE_CHANGE, 0);
  irCode = irCode >> 7;
  Serial.println(irCode);
  switch (irCode) {
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

    case BUTTON_SOUND: // color model
      if (getParameter(PARAM_COLOR_MODEL) > 8) {
        setAndSaveParameter(PARAM_COLOR_MODEL, 0);
      }
      else {
        incrementAndSaveParameter(PARAM_COLOR_MODEL);
      }
      break;
    case BUTTON_RIGHT:
      if (getParameter(PARAM_SPEED) < 6) {
        incrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON_LEFT:
      if (getParameter(PARAM_SPEED) > 0) {
        decrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON_AUTO: // number of waves
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

#ifdef BUTTON44
void eventIR44(unsigned long irCode) {
  irCode = irCode >> 7;
  Serial.println(irCode);

  // dealing with the loop through all existing modes
  if (irCode == BUTTON44_FADE7) {
    setAndSaveParameter(PARAM_AUTO_MODE_CHANGE, 1);
  } else {
    setAndSaveParameter(PARAM_AUTO_MODE_CHANGE, 0);
  }

  switch (irCode) {
    case  BUTTON44_ON_OFF:
      if (getParameter(PARAM_POWER) == 0) {
        setAndSaveParameter(PARAM_POWER, 1);
      } else {
        setAndSaveParameter(PARAM_POWER, 0);
      }
      break;
    case BUTTON44_PLAY:
      if (getParameter(PARAM_CHANGE) > 5) {
        setAndSaveParameter(PARAM_CHANGE, 0);
      }
      else {
        incrementAndSaveParameter(PARAM_CHANGE);
      }
      break;
#ifdef BUTTON44_BRIGHTER2
    case BUTTON44_BRIGHTER2:
#endif
    case BUTTON44_BRIGHTER:
      if (getParameter(PARAM_INTENSITY) < 7) {
        incrementAndSaveParameter(PARAM_INTENSITY);
      }
      break;
#ifdef BUTTON44_DIMMER2
    case BUTTON44_DIMMER2:
#endif
    case BUTTON44_DIMMER:
    case BUTTON_DOWN:
      if (getParameter(PARAM_INTENSITY) > 0) {
        decrementAndSaveParameter(PARAM_INTENSITY);
      }
      break;

    case BUTTON44_R:
      setAndSaveParameter(PARAM_COLOR_MODEL, 12);
      break;
    case BUTTON44_G:
      setAndSaveParameter(PARAM_COLOR_MODEL, 13);
      break;
    case BUTTON44_B:
      setAndSaveParameter(PARAM_COLOR_MODEL, 14);
      break;
    case BUTTON44_W:
      setAndSaveParameter(PARAM_COLOR_MODEL, 15);
      break;

    case BUTTON44_31 :
      setAndSaveParameter(PARAM_COLOR_MODEL, 0);
      break;
    case BUTTON44_32:
      setAndSaveParameter(PARAM_COLOR_MODEL, 1);
      break;
    case BUTTON44_33:
      setAndSaveParameter(PARAM_COLOR_MODEL, 2);
      break;
    case BUTTON44_34:
      if (getParameter(PARAM_COLOR_MODEL) != 3) {
        setAndSaveParameter(PARAM_CHANGE, 6);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, 3);
      break;
    case BUTTON44_41:
      setAndSaveParameter(PARAM_COLOR_MODEL, 4);
      break;
    case BUTTON44_42:
      setAndSaveParameter(PARAM_COLOR_MODEL, 5);
      break;
    case BUTTON44_43:
      setAndSaveParameter(PARAM_COLOR_MODEL, 6);
      break;
    case BUTTON44_44:
      setAndSaveParameter(PARAM_COLOR_MODEL, 7);
      break;
    case BUTTON44_51:
      setAndSaveParameter(PARAM_COLOR_MODEL, 8);
      break;
    case BUTTON44_52:
      setAndSaveParameter(PARAM_COLOR_MODEL, 9);
      break;
    case BUTTON44_53:
      setAndSaveParameter(PARAM_COLOR_MODEL, 11);
      break;
    case BUTTON44_54:
      setAndSaveParameter(PARAM_COLOR_MODEL, 16);
      break;
    case BUTTON44_61:
      setAndSaveParameter(PARAM_COLOR_MODEL, 18);
      break;
    case BUTTON44_62:
      setAndSaveParameter(PARAM_COLOR_MODEL, 19);
      break;
    case BUTTON44_63:
      setAndSaveParameter(PARAM_COLOR_MODEL, 20);
      break;
    case BUTTON44_64:
      setAndSaveParameter(PARAM_COLOR_MODEL, 21);
      break;

    case BUTTON44_QUICK:
      if (getParameter(PARAM_SPEED) < 6) {
        incrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON44_SLOW:
      if (getParameter(PARAM_SPEED) > 0) {
        decrementAndSaveParameter(PARAM_SPEED);
      }
      break;
    case BUTTON44_AUTO:
      setAndSaveParameter(PARAM_COLOR_MODEL, 10);
      break;
    case BUTTON44_FLASH:
      setAndSaveParameter(PARAM_COLOR_MODEL, 17);
      break;

    case BUTTON44_JUMP3:
      if (getParameter(PARAM_COLOR_MODEL) > -1) {
        decrementAndSaveParameter(PARAM_COLOR_MODEL);
      } else {
        setAndSaveParameter(PARAM_COLOR_MODEL, 21);
      }
      break;
    case BUTTON44_JUMP7:
      if (getParameter(PARAM_COLOR_MODEL) < 21) {
        incrementAndSaveParameter(PARAM_COLOR_MODEL);
      } else {
        setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      }
      break;

    case BUTTON44_RED_UP:
      if (getParameter(PARAM_RED_INTENSITY) < 7) {
        incrementAndSaveParameter(PARAM_RED_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;
    case BUTTON44_RED_DOWN:
      if (getParameter(PARAM_RED_INTENSITY) > 0) {
        decrementAndSaveParameter(PARAM_RED_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;
    case BUTTON44_GREEN_UP:
      if (getParameter(PARAM_GREEN_INTENSITY) < 7) {
        incrementAndSaveParameter(PARAM_GREEN_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;
    case BUTTON44_GREEN_DOWN:
      if (getParameter(PARAM_GREEN_INTENSITY) > 0) {
        decrementAndSaveParameter(PARAM_GREEN_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;
    case BUTTON44_BLUE_UP:
      if (getParameter(PARAM_BLUE_INTENSITY) < 7) {
        incrementAndSaveParameter(PARAM_BLUE_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;
    case BUTTON44_BLUE_DOWN:
      if (getParameter(PARAM_BLUE_INTENSITY) > 0) {
        decrementAndSaveParameter(PARAM_BLUE_INTENSITY);
      }
      setAndSaveParameter(PARAM_COLOR_MODEL, -1);
      break;

    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
#endif

void setupIR() {
  pinMode(1, INPUT);
  digitalWrite(1, HIGH);
  pinMode(MONITORING, OUTPUT);
  attachInterrupt(2, irInterrupt, CHANGE);
}
