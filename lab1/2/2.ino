int ledPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int _delay = 500;

void setup() {
  for (int i = 0; i != 10; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i != 5; ++i) {
    digitalWrite(ledPins[i], HIGH);
    delay(_delay);
    digitalWrite(ledPins[9 - i], HIGH);
    delay(_delay);
  }
  for (int i = 4; i != -1; --i) {
    digitalWrite(ledPins[9 - i], LOW);
    delay(_delay);
    digitalWrite(ledPins[i], LOW);
    delay(_delay);
  }
}