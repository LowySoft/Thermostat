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
    void   setID(String tID);               // Termosztát azonosító mentése
    void   setID(char* tID);                // Termosztát azonosító mentése

private:
    void   clearData(uint16_t addr, uint8_t maxSize);                 // Adatmező törlése
    String readString(uint16_t addr, uint8_t maxSize);                // EEPROMból String  olvasása
    void   writeString(String str, uint16_t addr, uint8_t maxSize);   // EEPROMba String írása
};

extern classThermSet thermSet;

#endif