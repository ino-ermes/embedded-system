// SD CARD READER
// MOSI: pin 11
// MISO: pin 12
// SCK: pin 13
// CS: pin 10

// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND

// DHT: DATA --> 9

#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>  // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
RtcDS1307<TwoWire> rtc(Wire);

DHT dht(9, DHT11);

const String fileName = "data.txt";

void setup() {
  Serial.begin(9600);

  dht.begin();
  rtc.Begin();

  rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
}


void sdWrite(String content, bool overwrite) {
  File file;
  if(overwrite) {
    file = SD.open(fileName, O_CREAT | O_WRITE);
  } else {
    file = SD.open(fileName, O_CREAT | O_WRITE | O_APPEND);
  }
  if (file) {
    Serial.println("Writing '" + content + "' into " + fileName);
    file.println(content);
    file.close();
  } else {
    Serial.println("error opening " + fileName);
  }
}


String dateStr(RtcDateTime dt) {
  char datestring[26];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  return datestring;
}

float last_temp = -1;

void loop() {
  float temp = dht.readTemperature();

  // Bai 2
  if (temp != last_temp) {
    RtcDateTime now = rtc.GetDateTime();
    sdWrite("Temp: " + String(temp) + "°C - Time: " + dateStr(now), false);
    last_temp = temp;
  }

  // Bai 1
  // RtcDateTime now = rtc.GetDateTime();
  // sdWrite("Temp: " + String(temp) + "°C - Time: " + dateStr(now), false);
  // delay(1000);
}