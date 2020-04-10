#ifndef _displayClass_h_
#define _displayClass_h_

#include <Arduino.h>

class displayClass
{
public:
    displayClass(); // OLED display osztály

    void begin();   // Kijelző élesztése
    void update();  // Kijelző frissítése
    void setServerConnect(bool connect = false);  // Szerver kapcsolat jelző

private:
    void drawMain();
    void updateStatLine();
    
    bool  blink :1;
    ulong lastTime;
};

extern displayClass OLED_display;

#endif