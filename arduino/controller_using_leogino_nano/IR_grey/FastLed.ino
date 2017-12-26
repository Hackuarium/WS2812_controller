
#define GREY1 6
#define GREY2 11


void initIntensity() {
  pinMode(GREY1, OUTPUT);
  pinMode(GREY2, OUTPUT);

}


void setIntensity() {
  if (getParameter(PARAM_POWER) == 0) {
    analogWrite(GREY1, 0);
    analogWrite(GREY2, 0);
  } else {
    analogWrite(GREY1, getParameter(PARAM_GREY1));
    analogWrite(GREY2, getParameter(PARAM_GREY2));
  }
}

