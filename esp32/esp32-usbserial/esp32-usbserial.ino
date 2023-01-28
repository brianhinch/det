int i;
const uint32_t DELAY_TIME = 1000;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello computer");
}

void loop() {
  i++;
  Serial.println(i);
  delay(DELAY_TIME);
}
