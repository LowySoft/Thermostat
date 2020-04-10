#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Thermometer.h"
#include "Network communikation/connect.h"
#include "thermSet.h"
#ifdef _OLED_Enable_
  #include "display.h"
#endif

Thermometer                        sensors;                            // sensor object
Connect                            wifiConnect;                        // WiFi connect object

void setup() {
  Serial.begin(9600);
  Serial.println("\nWelcode to the LowyTron Digital Thermostat V0.1 (C) 2020");
  Serial.printf("The CPU frequency is %i Mhz.\n\n", ESP.getCpuFreqMHz());
  thermSet.begin();                                 // Globális beállítások inicializálása

  // Begin dispay init
  #ifdef _OLED_Enable_
  OLED_display.begin();
  #endif

  // Begin sensor
  // sensors.begin_DS18(D3);
  sensors.begin_DHT(DHT22, D3);

  // Begin WiFi
  if (isWiFiEnable) {
    if (!wifiConnect.begin())   // Ha nem sikerűlt kapcsolódni a WiFi-hez
      wifiConnect.beginAP();    // autómatikussan AP módba kapcsól
    else
      wifiConnect.begin_mDNS();// Ha kapcsolódott, mDNS indítása

    wifiConnect.beginServer();
    
    configTime(2 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  }
}

void loop() {
  wifiConnect.loop();
  sensors.loop();

  #ifdef _OLED_Enable_
  OLED_display.update();
  #endif
}
