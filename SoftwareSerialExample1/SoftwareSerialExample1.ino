#include <SoftwareSerial.h>
#include <Wire.h>  // i2c
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     0 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(D5, D6); // RX, TX

static const unsigned PROGMEM char humid [] = {
0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00,
0x03, 0x04, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x0C, 0x01, 0x00, 0x00,
0x08, 0x01, 0x00, 0x00, 0x18, 0x00, 0x80, 0x00, 0x10, 0x00, 0x80, 0xC0, 0x30, 0x00, 0x41, 0xA0,
0x28, 0x00, 0x43, 0x30, 0x28, 0x00, 0x42, 0x10, 0x28, 0x00, 0x46, 0x08, 0x28, 0x00, 0x44, 0x08,
0x2C, 0x00, 0x4C, 0x04, 0x14, 0x00, 0xC8, 0x14, 0x12, 0x00, 0x88, 0x14, 0x09, 0x81, 0x8C, 0x34,
0x04, 0x03, 0x04, 0xE8, 0x03, 0xFC, 0x46, 0x08, 0x00, 0x00, 0xE3, 0xF0, 0x00, 0x00, 0xB0, 0x00,
0x00, 0x01, 0x10, 0x00, 0x00, 0x03, 0x18, 0x00, 0x00, 0x02, 0x08, 0x00, 0x00, 0x02, 0x88, 0x00,
0x00, 0x02, 0x88, 0x00, 0x00, 0x02, 0xC8, 0x00, 0x00, 0x01, 0x18, 0x00, 0x00, 0x00, 0xF0, 0x00
};

static const unsigned PROGMEM char temp [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00,
0x00, 0x02, 0x40, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x05, 0xA0, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x0B, 0xD0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x04, 0x20, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  
  pinMode(D3, INPUT);
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
   }
   
  mySerial.begin(9600);
  dht.begin();
}

void loop() { // run over and over 
  delay(1000);
  char command;
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  draw(t, h);

  
  if (mySerial.available()) {
    command = mySerial.read();
    switch(command){
      case 't':
        mySerial.print(t,1);
        mySerial.print(" C");
        mySerial.println();
        break;
      case 'h':
        
        mySerial.print(h, 1);
        mySerial.print(" %");
        mySerial.println();
        break;
      case 'a':
        digitalWrite(D0, LOW);
        mySerial.print("LED ON!!");
        mySerial.println();
        break;
      case 'b':
        digitalWrite(D0, HIGH);
        mySerial.print("LED OFF!!");
        mySerial.println();
        break;
    }
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
void draw(float t, float h){
  display.clearDisplay();
  display.drawBitmap(0, 0, temp, 30, 30, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40, 15);
  display.print("TEMP : ");
  display.print(t, 1);
  display.print("C");
  display.drawBitmap(0, 32, humid, 30, 30, WHITE);
  display.setCursor(40, 47);
  display.print("HUM : ");
  display.print(h, 1);
  display.print("%");
  display.drawRect(0, 0, 128, 64, WHITE);
  display.drawLine(0, 32, 128, 32, WHITE);
  display.drawLine(33, 0, 33, 64, WHITE);
  display.display();
}
