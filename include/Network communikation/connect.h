#ifndef Connect_h
#define Connect_h

#include <Arduino.h>

#define AP_SSID  "LowySoft Termostat"   // Szerver SSID neve
#define AP_PASS  NULL                   // Szerver jelszava

class Connect
{
private:
    enum {
        notConnect      = 0,
        modeAP          = 1,
        modeClient      = 2,
        modeRunServer   = 4,
        modeRunmDNS     = 8
    } mode_e;

public:
    Connect();
    ~Connect();

    boolean begin();        // Csatlakozni próbál
    boolean beginAP();      // AP mód indítása
    void begin_mDNS();      // mDNS indítása
    void beginServer();     // Web szerver indítása
    void loop();            // loop ciklus függvény

private:
    boolean readNetworkData();  // Beolvassa eeprom-ból a hállózati adatokat, ha kell, inicializálja
    void    createWebServer();  // Web szerver létrehozása
    
private:
    uint8_t mode;        // Üzemmód jelző
};


#endif