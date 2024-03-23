int ledPins[] = { A0, A1, A2, A3, A4 };
int brightnessPin = A5;
int brightness = 0;

void setup() {
}

void loop() {
  brightness = analogRead(brightnessPin);
  for (int i = 0; i < 5; ++i) {
    analogWrite(ledPins[i], brightness);
  }
}
