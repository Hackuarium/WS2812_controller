
void update() {



  if (getParameter(PARAM_POWER) == 0) {
    black();
    Serial.println(getParameter(PARAM_SPECIAL_CONFIG));
    if (getParameter(PARAM_SPECIAL_CONFIG) > 0) {
      Serial.println("Config");
      setParameter(PARAM_SPECIAL_CONFIG, getParameter(PARAM_SPECIAL_CONFIG) - 1);
      // need to display the current config parameters
      for (byte line = 0; line < LINES; line++) {
        for (byte i = 0; i < getParameter(PARAM_COLOR_CHANGE_SPEED); i++) {
          colors[getLed(line, i)] =  rgb_color(255, 0, 0);
        }
      }
    }

    return;
  }
  switch (getParameter(PARAM_CURRENT_PROGRAM)) {
    case 0:
      updateRain();
      break;
    case 1:
      updateComet(0);
      break;
    case 2:
      updateComet(1);
      break;
    case 3:
      updateWave(0);
      break;
    case 4:
      updateWave(1);
      break;
    case 5:
      updateTree();
      break;
    case 6:
      updateFirework();
      break;
    case 7:
      updateColorTree();
      break;
  }
}
