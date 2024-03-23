#include <SPI.h>
#include <MFRC522.h>

/*

RST       9
SDA(SS)   10
MOSI      11
MISO      12
SCK       13

LED       8

*/

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int ledPin = 8;
int validId[4] = { 67, 102, 188, 149 };

enum Mode {
  VALID,
  INVALID,
  DOUBLE_VALID
};

Mode curMode = VALID;
bool isLedOn = true;

unsigned long long singleValidTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522
  delay(4);            // Optional delay. Some board do need more time after init to be ready, see Readme
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  int id[4];
  for (int i = 0; i < 4; ++i) {
    id[i] = mfrc522.uid.uidByte[i];
    Serial.print(id[i]);
    Serial.print(" ");
  }
  Serial.println("");

  if (isValidId(id)) {
    if (curMode == VALID && millis() - singleValidTime < 5000) {
      curMode = DOUBLE_VALID;
    } else {
      curMode = VALID;
      singleValidTime = millis();
    }
  } else {
    curMode = INVALID;
  }

  switch (curMode) {
    case VALID:
      isLedOn = true;
      break;
    case DOUBLE_VALID:
      isLedOn = false;
      break;
    case INVALID:
      isLedOn = !isLedOn;
      break;
  }
  digitalWrite(ledPin, isLedOn);
}

bool isValidId(const int* id) {
  for (int i = 0; i < 4; ++i) {
    if (id[i] != validId[i]) return false;
  }
  return true;
}