int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

int value = 0;

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();

    int redIdx = input.indexOf('R');
    int greenIdx = input.indexOf('G');
    int blueIdx = input.indexOf('B');
    int delayIdx = input.indexOf('D');

    if (redIdx != -1) {
      value = myToInt(input, redIdx + 1);
      analogWrite(redPin, constrain(value, 0, 255));
    }
    if (greenIdx != -1) {
      value = myToInt(input, greenIdx + 1);
      analogWrite(greenPin, constrain(value, 0, 255));
    }
    if (blueIdx != -1) {
      value = myToInt(input, blueIdx + 1);
      analogWrite(bluePin, constrain(value, 0, 255));
    }
    if (delayIdx != -1) {
      value = myToInt(input, delayIdx + 1);
      delay(constrain(value, 0, 999) * 1000);
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }
  }
}

int myToInt(const String &str, const int &startIndex) {
  int len = str.length();

  bool valid = 0 <= startIndex && startIndex < len;
  if (!valid) return 0;

  int endIndex = startIndex - 1;
  while ((endIndex + 1) < len && '0' <= str.charAt(endIndex + 1) && str.charAt(endIndex + 1) <= '9')
    ++endIndex;
  int result = 0;
  int scale = 1;
  for (int i = endIndex; i >= startIndex; --i) {
    result += scale * (str.charAt(i) - '0');
    scale *= 10;
  }
  return result;
}
