int i;
const uint32_t DELAY_TIME = 1000;

long hallValue;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello computer");
}

void loop() {
  hallValue = hallRead();
  Serial.println((double)hallValue / 1000.);
}
