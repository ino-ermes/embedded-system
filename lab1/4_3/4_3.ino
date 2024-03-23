int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int delayPin = A0;
int _delay = 500;

void setup() {
  for (int i = 0; i != 10; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int j = 0; j < 2; ++j) {
    for (int i = j; i < 10; i += 2) {
      digitalWrite(ledPins[i], HIGH);
      _delay = analogRead(delayPin);
      delay(_delay);
    }
  }
  for (int j = 0; j < 2; ++j) {
    for (int i = j; i < 10; i += 2) {
      digitalWrite(ledPins[i], LOW);
      _delay = analogRead(delayPin);
      delay(_delay);
    }
  }
}