
void update() {
  if (getParameter(PARAM_POWER)) {
black();
    return;
  }
  switch (getParameter(PARAM_CURRENT_PROGRAM)) {
    case 0:
      updateRain();
      break;
    case 1:
      updateComet();
      break;
  }
}
