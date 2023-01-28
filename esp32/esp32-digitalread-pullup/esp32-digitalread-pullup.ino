int i;
const uint32_t DELAY_TIME = 1;

const int BUTTON_PIN = 17;
int buttonState;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello computer");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);

  delay(DELAY_TIME);
}
