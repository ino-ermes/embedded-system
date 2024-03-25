// SD CARD READER
// MISO: pin 12
// MOSI: pin 11
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
const bool overwrite = true;
float lastTemp = -1;

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

  // if(overwrite && SD.exists(fileName)) {
  //   SD.remove(fileName);
  // }

  if (overwrite && SD.exists(fileName)) {
    File file = SD.open(fileName, O_WRITE | O_TRUNC);  // Open file for writing and truncate its content
    if (file) {
      file.close();  // Close file to remove its content
      // Serial.println("Content of " + fileName + " removed.");
    } else {
      Serial.println("error opening " + fileName);
    }
  } else {
    lastTemp = getLastTemperature();
    Serial.println(lastTemp);
  }
}


void sdWrite(String content) {
  File file = SD.open(fileName, O_CREAT | O_WRITE | O_APPEND);
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

float getLastTemperature() {
  File file = SD.open(fileName);
  if (file) {
    // Seek to the end of the file
    unsigned long fileSize = file.size();
    if(fileSize < 1) return -1;
    unsigned long seekPos = fileSize - 2;

    file.seek(seekPos);

    // Find the start of the last line
    while (seekPos > 0 && file.read() != '\n') {
      seekPos--;
      file.seek(seekPos);
    }

    // Read the last line
    String lastLine = file.readString();
    file.close();

    // Extract temperature from the last line
    int tempIndex = lastLine.indexOf("Temp: ");
    if (tempIndex != -1) {
      int tempEndIndex = lastLine.indexOf("°C", tempIndex);
      if (tempEndIndex != -1) {
        String tempStr = lastLine.substring(tempIndex + 6, tempEndIndex);
        return tempStr.toFloat();
      }
    }
  } else {
    Serial.println("Error opening " + fileName);
  }

  // If something went wrong, return a default value
  return -1;
}

void loop() {
  float temp = dht.readTemperature();
  if(isnan(temp)) {
    Serial.println("temp is nan");
  }

  // Bai 2
  // if (fabs(temp - lastTemp) > 0.01) {
  //   RtcDateTime now = rtc.GetDateTime();
  //   sdWrite("Temp: " + String(temp, 2) + "°C - Time: " + dateStr(now));
  //   lastTemp = temp;
  // }

  // Bai 1
  RtcDateTime now = rtc.GetDateTime();
  sdWrite("Temp: " + String(temp) + "°C - Time: " + dateStr(now));
  delay(1000);
}