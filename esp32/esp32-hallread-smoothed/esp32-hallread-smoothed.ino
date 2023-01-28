int i;
const uint32_t DELAY_TIME = 100;

long hallValue;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello computer");
}

void loop() {
  hallValue = 0;
  for (i = 0; i < 1000; i++) {
    hallValue += hallRead();
    delayMicroseconds(DELAY_TIME_US);
  }
  Serial.println((double)hallValue / 1000.);
}
