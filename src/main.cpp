#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <OneWire.h>
#include "Thermometer.h"

#include "ESP8266WiFi.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);    // OLED Dislpay object
Thermometer                        sensors;

typedef struct {
  uint8_t blink   :1;   // Villogás állapota
} thStatusType;

thStatusType thStatus;                                                // Sztátuszjeljő bitek

void setup() {
  Serial.begin(9200);
  Serial.println("\nWelcode to the LowyTron Digital Thermostat V0.1 (C) 2020");

  // Begin dispay init
  display.begin();
  display.setFont(u8g2_font_helvB10_te);
  display.drawStr(10, 25, "Digital Thermostat");
  display.drawStr(50, 40, "V: 0.1");
  display.sendBuffer();

  sensors.begin_DHT(DHT12, D4);
  sensors.begin_DS18(D3);
}

char  str[30], str2[30];
unsigned long lastPri = 0;

void loop() {
  sensors.loop();
  
  if ((millis() - lastPri) >= 500) {
    thStatus.blink = !thStatus.blink;
    lastPri = millis();
  }

  sprintf(str, "Sen. 1: %02.01f°C", sensors.getThemp());
  sprintf(str2, "Sen. 2: %02.01f°C", sensors.getThemp(1));

  display.firstPage();
  do {
    if (thStatus.blink) {
      display.setFont(u8g2_font_open_iconic_all_1x_t);
      display.drawGlyph(120, 8, 0x00f7);
    }

    display.setFont(u8g2_font_helvB10_te);
    display.drawUTF8(4, 20, "Hőfok:");

    display.drawUTF8(10, 35, str);
    display.drawUTF8(10, 50, str2);
    
  } while ( display.nextPage() );

}