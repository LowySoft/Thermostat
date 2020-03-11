#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>

#include <U8g2lib.h>
#include "Thermometer.h"
#include "Network communikation/connect.h"
#include "thermSet.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);    // OLED Dislpay object
Thermometer                        sensors;                            // sensor object
Connect                            wifiConnect;                        // WiFi connect object


typedef struct {
  uint8_t blink   :1;   // Villogás állapota
} thStatusType;


thStatusType thStatus;      // Sztátuszjeljő bitek
bool         isWifiConfig;  // Volt configurálva a WiFi?

void setup() {
  Serial.begin(9600);
  Serial.println("\nWelcode to the LowyTron Digital Thermostat V0.1 (C) 2020");
  thermSet.begin();                                 // Globális beállítások inicializálása

  // Begin dispay init
  display.begin();
  display.setFont(u8g2_font_helvB10_te);
  display.drawStr(0, 25, "Digital Thermostat");
  display.drawStr(50, 40, "V: 0.1");
  display.sendBuffer();

  // Begin sensor
  sensors.begin_DS18(D3);

  // Begin WiFi
  isWifiConfig = wifiConnect.begin();
  
  if (!isWifiConfig) 
    wifiConnect.beginAP();

  wifiConnect.begin_mDNS();
  wifiConnect.beginServer();
}

char  str[100];
unsigned long lastPri = 0;

void loop() {
  sensors.loop();
  wifiConnect.loop();

  if ((millis() - lastPri) >= 500) {
    thStatus.blink = !thStatus.blink;
    lastPri = millis();
  }

  display.firstPage();
  do {
    if (thStatus.blink || WiFi.status() == WL_CONNECTED) {
      display.setFont(u8g2_font_open_iconic_all_1x_t);
      display.drawGlyph(120, 8, 0x00f7);
    }

    display.setFont(u8g2_font_helvB10_te);
    display.drawUTF8(4, 20, "Hőfok:");

    sprintf(str, "Sen. 1: %02.01f°C", sensors.getThemp());
    display.drawUTF8(10, 35, str);
    sprintf(str, "Sen. 2: %02.01f°C", sensors.getThemp(1));
    display.drawUTF8(10, 50, str);
    
  } while ( display.nextPage() );
}
