
void update() {
  if (getParameter(PARAM_POWER) == 0) {
    black();
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
      updateTinsel();
      break;
  }
}
