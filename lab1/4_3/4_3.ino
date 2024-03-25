int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int delayPin = A0;
int _delay = 500;

void setup() {
  for (int i = 0; i != 10; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // for (int j = 1; j >= 0; --j) {
  //   for (int i = j; i < 10; i += 2) {
  //     digitalWrite(ledPins[i], HIGH);
  //     _delay = analogRead(delayPin);
  //     delay(_delay);
  //   }
  // }
  // for (int j = 1; j >= 0; --j) {
  //   for (int i = j; i < 10; i += 2) {
  //     digitalWrite(ledPins[i], LOW);
  //     _delay = analogRead(delayPin);
  //     delay(_delay);
  //   }
  // }

  // Version 2
  for (int i = 1; i <= 9; i += 2) {
    digitalWrite(ledPins[i], HIGH);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
  for (int i = 8; i >= 0; i -= 2) {
    digitalWrite(ledPins[i], HIGH);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
  for (int i = 1; i <= 9; i += 2) {
    digitalWrite(ledPins[i], LOW);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
  for (int i = 8; i >= 0; i -= 2) {
    digitalWrite(ledPins[i], LOW);
    _delay = analogRead(delayPin);
    delay(_delay);
  }
}