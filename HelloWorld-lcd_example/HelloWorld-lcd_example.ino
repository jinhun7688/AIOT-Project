#include <Wire.h> //아두이노에서 제공하는 i2c 라이브러리
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN D7
#define DHTTYPE DHT11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//0x27은 해당 번지에 있는 놈만 대답하라는 고유번지를 의미한다.
//i2c통신을 하기 위해서 공장에서 지정된 주소이다.

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
}

void loop()
{ 
  delay(2000);
  lcd.clear();
  delay(100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  lcd.setCursor(0,0);
  lcd.print("Hum: ");
  lcd.print(h, 1);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(t, 1);
  lcd.print("'C");
}
