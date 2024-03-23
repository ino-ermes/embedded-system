int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int delayPin = A0;
int _delay = 500;

void setup() {
  for (int i = 0; i != 10; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i != 10; ++i) {
    digitalWrite(ledPins[i], HIGH);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
  for (int i = 9; i != -1; --i) {
    digitalWrite(ledPins[i], LOW);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
}
