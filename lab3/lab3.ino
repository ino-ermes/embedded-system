#include <LiquidCrystal_I2C.h>
#include <DHT.h>

/*

SCL     A5
SDA     A4
DHT     2
Button  3

*/

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUTTON_PIN 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool isFahrenheit = false;  // Biến lưu đơn vị nhiệt độ, false là °C, true là °F
bool isOffScreen = false;

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

unsigned long long time;
void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    while (digitalRead(BUTTON_PIN) == HIGH) delay(5);
    isFahrenheit = !isFahrenheit;
    time = millis();
    int dbClick = 0;
    while ((dbClick = digitalRead(BUTTON_PIN)) != HIGH) {
      if (millis() - time > 300) break;
    }
    if (dbClick) {
      if(isOffScreen) {
        lcd.backlight();
        lcd.display();
      } else {
        lcd.noBacklight();  // Tắt đèn nền LCD
        lcd.noDisplay();
      }
      isOffScreen = !isOffScreen;
      isFahrenheit = !isFahrenheit;
    }
  }

  float t = dht.readTemperature(isFahrenheit);  // Đọc nhiệt độ theo đơn vị hiện tại
  if (isnan(t)) {
    lcd.print("Error");  // Nếu không đọc được nhiệt độ, hiển thị lỗi
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do:");
  lcd.setCursor(0, 1);
  lcd.print(t);
  lcd.print((char)223);
  lcd.print(isFahrenheit ? "F" : "C");  // Hiển thị đơn vị tùy thuộc vào giá trị của isFahrenheit

  delay(100);
}