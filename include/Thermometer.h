#ifndef Thermometer_h
#define Thermometer_h

#ifdef __cplusplus

#include <stdint.h>

#if defined(__AVR__)
#include <util/crc16.h>
#endif

#if ARDUINO >= 100
#include <Arduino.h>       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <DallasTemperature.h>
#include <DHT.h>

#define  ThermometerMaxSensors 8    // Maximális szenzórok száma
#define  ThermometerResolution 12   // Hőmérsékleti adatok felbontása a Dallas hőmérőkhöz. Értéke 9 - 12 bit.

class Thermometer {

private:
    enum {
        notMode = 0,
        ModeDS18,
        ModeDHT
    } Mode;

    typedef struct
    {
        uint8_t       mode       : 2,   // Aktuális üzemmód
                      changeMode : 2;   // Üzemmódváltási kérelem
        uint8_t       reg1;             // PinNum az üzemmódváltáshoz
        uint8_t       reg2;             // DHT Type az üzemmódváltáshoz
    } status_t;

    DallasTemperature *Sensor;          // DS18xxx objectum
    DHT               *dht = NULL;      // DHT objectum
    DeviceAddress     senAddress[ThermometerMaxSensors];    // Dallas szenzorok címei
    float             senTemps[ThermometerMaxSensors];      // Mért hőmérségleti adatok
    float             humidity;        // Mért páratartalom
    uint8_t           senNum;          // Szenzorok száma 
    unsigned long     lastRequest;     // Utolsó olvasás időbéjege
    int16_t           delayInMillis;   // Várakozási idő sensor olvasáshoz
    status_t          status;          // Thermometer status regiszter 

public:
    Thermometer();
    ~Thermometer();
    void       begin_DS18(uint8_t pinNum);                  // DS18xxx Dallas szenzór indítása
    void       begin_DHT(uint8_t dhtType, uint8_t pinNum);  // DHT szenzór indítása
    void       loop();                                      // 
    uint8_t    getSensorsNum() { return senNum;};           // Szenzorok száma
    boolean    isHumidity();                                // Van Páratartalom mérő?
    float      getThemp(uint8_t thempNum = 0);              // Hőmérségleti adatok lekérdezése
    float      getHumidity();                               // Párataltalom lekérdezése

private:
    void        loop_DS18();
    void        loop_DHT();
    void        reBegin();
    void        copyAddress(uint8_t* source, uint8_t* dest);

};


#endif  // __cplusplus
#endif  // Thermometer_h