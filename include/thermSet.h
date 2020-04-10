/*************************************************
 *
 *  Thermostat beállításainak tárolása, kezelése 
 * 
 *  LowySoft (C) 2020
 */

#ifndef thermSet_h
#define thermSet_h

#include <Arduino.h>

#define thermostatDefId "Termosztát"

#define WiFi_Enable         thermSet.set(tsFlag_WiFi, 1)        // WiFi kommunikáció engedélyezése
#define WiFi_Disable        thermSet.set(tsFlag_WiFi, 0)        // WiFi kommunikáció tiltása
#define isWiFiEnable        thermSet.get(tsFlag_WiFi)           // WiFi engedélyezve?
#define HeatIndex_Enable    thermSet.set(tsFlag_HeatIndex , 1)  // Hőérzet használatának engedélyezése
#define HeatIndex_Disable   thermSet.set(tsFlag_HeatIndex , 0)  // Hőérzet használatának tiltása
#define isHeatIndexEnable   thermSet.get(tsFlag_HeatIndex)      // Hőérzet használva?

enum {
    tsFlag_WiFi     = 0x01,     // WiFi ki/be-kapcsolás
    tsFlag_HeatIndex= 0x02,     // Hőérzet
    tsFlag_unused6  = 0x04,
    tsFlag_unused5  = 0x08,
    tsFlag_unused4  = 0x10,
    tsFlag_unused3  = 0x20,
    tsFlag_unused2  = 0x40,
    tsFlag_unused1  = 0x80,
};

class classThermSet
{
private:
    /* data */
public:
    classThermSet();
    ~classThermSet();

    void   begin();                         // EEPROM inicializálása

    String getSSID();                       // WiFi SSID lekérdezése
    void   setSSID(String tSSID);           // WiFi SSID mentése
    void   setSSID(char* tSSID);            // WiFi SSID mentése

    String getPassworld();                  // WiFi jelszó lekérdezése
    void   setPassworld(String tPass);      // WiFi jelszó mentése
    void   setPassworld(char* tPass);       // WiFi jelszó mentése

    String getID();                         // Termosztát azonosító lekérdezése
    String getHardwareID();                 // Termosztát eszközazonosító (Chip id-thermostat)
    void   setID(String tID);               // Termosztát azonosító mentése
    void   setID(char* tID);                // Termosztát azonosító mentése

    void   set(uint8_t flagBit, bool status);   // Jelzőbitek állítása
    bool   get(uint8_t flagBit);                // Jelzőbitek olvasása

private:
    void   clearData(uint16_t addr, uint8_t maxSize);                 // Adatmező törlése

    String readString(uint16_t addr, uint8_t maxSize);                // EEPROMból String  olvasása
    void   writeString(String str, uint16_t addr, uint8_t maxSize);   // EEPROMba String írása
};

extern classThermSet thermSet;

#endif