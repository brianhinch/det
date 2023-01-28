int i;
const uint32_t DELAY_TIME = 1;

const int TOUCH_PIN = T0;
long touchValue;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello computer");
}

void loop() {
  touchValue = 0;
  for (i = 0; i < 1000; i++) {
    touchValue += touchRead(TOUCH_PIN);
    delay(DELAY_TIME);
  }
  Serial.println((double)touchValue / 1000.);
}
