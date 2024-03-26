const int ledPinRed = 9;
const int ledPinGreen = 10;
const int ledPinBlue = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int rIndex = data.indexOf('R');
    int gIndex = data.indexOf('G');
    int bIndex = data.indexOf('B');
    int tIndex = data.indexOf('D');

    int redValue = data.substring(rIndex + 1, gIndex).toInt();
    int greenValue = data.substring(gIndex + 1, bIndex).toInt();
    int blueValue = data.substring(bIndex + 1).toInt();
    int timeValue = data.substring(tIndex + 1).toInt();

    redValue = min(redValue, 255);
    greenValue = min(greenValue, 255);
    blueValue = min(blueValue, 255);

    if (rIndex != -1) analogWrite(ledPinRed, redValue);
    if (gIndex != -1) analogWrite(ledPinGreen, greenValue);
    if (bIndex != -1) analogWrite(ledPinBlue, blueValue);

    if (tIndex != -1) {
      delay(timeValue * 1000);
      if (rIndex == -1 && gIndex == -1 && bIndex == -1) {
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinGreen, 0);
        analogWrite(ledPinBlue, 0);
      } else {
        if (rIndex != -1) analogWrite(ledPinRed, 0);
        if (gIndex != -1) analogWrite(ledPinGreen, 0);
        if (bIndex != -1) analogWrite(ledPinBlue, 0);
      }
    }
  }
}