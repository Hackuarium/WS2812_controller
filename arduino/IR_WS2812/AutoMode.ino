unsigned int counter = 0;
void autoMode() {
  counter++;
  if (getParameter(PARAM_AUTO_MODE_CHANGE) == 1 && counter % AUTOCHANGE_VALUE == 0) {
    if (getParameter(PARAM_COLOR_MODEL) < 21) {
      incrementAndSaveParameter(PARAM_COLOR_MODEL);
    } else {
      setParameter(PARAM_COLOR_MODEL, -1);
    }
    counter = 0;
  }

}


