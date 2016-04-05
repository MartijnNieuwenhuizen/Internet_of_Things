int delayAmount = 100;

void setup() {
  pinMode(D1, OUTPUT);
}

void loop() {
  digitalWrite(D1, LOW);
  delay(delayAmount);
  digitalWrite(D1, HIGH);
  delay(delayAmount);
}
