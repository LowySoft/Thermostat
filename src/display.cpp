#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <time.h>

#include "display.h"
#include "Thermometer.h"
#include "thermSet.h"
#include "Network communikation\connect.h"

extern Thermometer sensors;
extern Connect     wifiConnect;

#define thIcon_WiFi     0x00f7
#define thIcon_Server   0x00e6  // 0104, 00d6

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);     // OLED Dislpay object
displayClass                       OLED_display;                        // Thermostat OLED display object

static const char str_AP[] PROGMEM = "AP";

typedef struct {
    uint8_t serverConnect : 1; // server kapcsolat jelző
} t_flags;

t_flags flags;
char str[25];

displayClass::displayClass() {
    lastTime            = millis();
    blink               = false;
    flags.serverConnect = 0;
}

// Kijelző élesztése
void displayClass::begin() {
    display.begin();
    display.setFont(u8g2_font_helvB10_te);
    display.drawStr(0, 25, "Digital Thermostat");
    display.drawStr(50, 40, "V: 0.1");
    display.sendBuffer();
}

void displayClass::setServerConnect(bool connect)
{
    if (connect == false)
        flags.serverConnect = 0;
    else
        flags.serverConnect = 1;
}

// Kijelző frissítése
void displayClass::update()
 {

     // Villogtatás ritmusa
    if ((millis() - lastTime) >= 500) {
        blink = !blink;
        lastTime = millis();
    }

    // Display frissítése
    display.firstPage();
    do {
        updateStatLine();
        drawMain();
    } while ( display.nextPage() );

}

//////////////////////////////////////////
//
//  Private funktions

void displayClass::drawMain()
{
    float temp1, temp2;
    u8g2_uint_t pozX;

    if (isHeatIndexEnable) {
        temp1 = sensors.getHeatIndex();
        temp2 = sensors.getThemp();
    } else {
        temp1 = sensors.getThemp();
        temp2 = sensors.getHeatIndex();
    }

        display.setFont(u8g2_font_helvB24_te);
        sprintf(str, "%02.01f °C", temp1);
        display.drawUTF8(8, 40, str);

        if (sensors.isHumidity()) {
            display.setFont(u8g2_font_helvB08_te);
            sprintf(str, "Páratartalom: %02.01f %%", sensors.getHumidity());
            pozX = (128 - display.getStrWidth(str)) / 2;
            display.drawUTF8(pozX, 54, str);

            sprintf(str, "%s: %02.01f °C", isHeatIndexEnable ? "Hőfok" : "Hőérzet",  temp2);
            pozX = (128 - display.getStrWidth(str)) / 2;
            display.drawUTF8(pozX, 64, str);
        }

}

void displayClass::updateStatLine()
{
    uint8_t pozX = 128;
    time_t  raw_time;
    struct tm* timeinfo;

    // WiFi status jelzők
    if (WiFi.getMode() != WIFI_OFF) {
        pozX -= 8;

        // WiFi status kijelzése
        if (blink || WiFi.status() == WL_CONNECTED) {
            display.setFont(u8g2_font_open_iconic_all_1x_t);
            display.drawGlyph(pozX, 8, thIcon_WiFi);
        }
    
         if (wifiConnect.isAPmode()) {
            pozX -= 20;
            strcpy_P(str, (PGM_P)str_AP);
            display.setFont(u8g2_font_helvB08_te);
            display.drawUTF8(pozX, 8, str);
        }
    }

    // Server kapcsolat jelző
    if (flags.serverConnect) {
        pozX -= 10;
        display.setFont(u8g2_font_open_iconic_all_1x_t);
        display.drawGlyph(pozX, 8, thIcon_Server);
    }

    // Print time
    display.setFont(u8g2_font_helvB10_te);
//    if (WiFi.status() == WL_CONNECTED) {
        time(&raw_time);
        timeinfo = localtime(&raw_time);
        sprintf(str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//    } else {
//        sprintf(str, "--:--:--");
//    }

    display.drawUTF8(0, 11, str);
}