int ledPins[] = { 5, 6, 9, 10, 11 };
int brightnessPin = A5; 
int brightness = 0;

void setup() {
  for (int i = 0; i < 5; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  brightness = analogRead(brightnessPin) / 4;
  for (int i = 0; i < 5; ++i) {
    analogWrite(ledPins[i], brightness);
  }
}
