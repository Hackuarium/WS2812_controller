

#define LED_PIN     5


#define PARAM_POWER          0
#define PARAM_GREY1         1
#define PARAM_GREY2         2


#define PARAM_LAST_KEY       25

int unsigned irCode = 0;
int unsigned newIrCode = 0;

void setup() {
  Serial.begin(9600);
  setupParameters();
  initIntensity();
  setupIR();
}

void loop() {
  delay(500);
  setIntensity();

  
  Serial.print(irCode);
  Serial.print(" ");
  Serial.print(getParameter(PARAM_LAST_KEY));
  Serial.print(" ");
  Serial.println(getParameter(PARAM_POWER));
   setParameter(PARAM_LAST_KEY,0);
}


