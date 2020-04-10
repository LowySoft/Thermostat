#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include "Thermometer.h"

#define delayInMillis_DS18 (750 / (1 << (12 - ThermometerResolution)))   // Várakozási idő milliszekundumban a Dallas hőmérőkhöz
#define delayInMillis_DHT  2000                                          // Várakozási idő milliszekundumban a DHT hőmérőkhöz

OneWire thermWire;

Thermometer::Thermometer()
{
    int i;

     for(i = 0; i < ThermometerMaxSensors; i++)
        senTemps[i] = 0;

    senNum = 0;
    status.changeMode = status.mode = notMode;
}

Thermometer::~Thermometer()
{
    if (dht)
        delete dht;
    if (Sensor)
        delete Sensor;
}

void Thermometer::begin_DS18(uint8_t pinNum)
{
    int i, j, c;
    DeviceAddress current;

    if( status.mode != notMode) {               // Módváltási kérelem
        status.changeMode = ModeDS18;
        status.reg1 = pinNum;
        return;
    }

    thermWire.begin(pinNum);
//    Sensor.setOneWire(&thermWire);
    Sensor = new DallasTemperature(&thermWire);
    if (Sensor == NULL) {
        Serial.println("\nThermometer: Not enought memory to creade DS18xxx temperature object.\n");
        return;
    }

    Sensor->begin();

   j = Sensor->getDeviceCount();
    for(i = 0, c = 0; i < j; i++) {
        if (c == ThermometerMaxSensors)
            break;
        Sensor->getAddress(current, i);                  // Következő szenzór címe
        if(Sensor->validFamily(current)) {               // Ha hőmérő szenzór
            copyAddress(current,  senAddress[c++]);      // eltáróljuk
            Sensor->setResolution(current, ThermometerResolution);          // Pontosság beállítása
        }
    }
    senNum = c;

    Sensor->setWaitForConversion(false);
    Sensor->requestTemperatures();
    delayInMillis = delayInMillis_DS18;
    lastRequest = millis();
    status.mode = ModeDS18;
}

void Thermometer::begin_DHT(uint8_t DhtType, uint8_t pinNum)
{
    if( status.mode != notMode) {       // Módváltási kérelem
        status.changeMode = ModeDHT;
        status.reg1 = pinNum;
        status.reg2 = DhtType;
        return;
    }

    dht = new DHT(pinNum, DhtType);
    if (dht == NULL) {
        Serial.println("\nThermometer: Not enought memory to creade DHT object.\n");
        return;
    }

    senNum = 1;
    humidity = 0;
    senTemps[0] = 0;
    
    dht->begin();
    delayInMillis = delayInMillis_DHT;
    lastRequest = millis();
    status.mode = ModeDHT;
}

float Thermometer::getThemp(uint8_t sensorNum)
{
    if (sensorNum < ThermometerMaxSensors)
        return senTemps[sensorNum];

    return 0;
}

float Thermometer::getHumidity()
{
    if (dht)
        return humidity;
    else
        return 0;
}

float Thermometer::getHeatIndex()
{
    if (dht)
        return dht->computeHeatIndex(senTemps[0], humidity, false);
    else
        return 0;
}

boolean Thermometer::isHumidity()
{
    return dht == NULL ? false : true;
}

void Thermometer::loop()
{
    if (senNum == 0)
        return;

    if ( (millis() - lastRequest) >= delayInMillis)
    {
        if (status.mode == ModeDS18)
            loop_DS18();
        if (status.mode == ModeDHT)
            loop_DHT();

        if (status.changeMode != notMode)
            reBegin();
        else
            lastRequest = millis();
    }
}

////////////////
// Private

void Thermometer::loop_DS18()
{
    for(int i = 0; i < senNum; i++)
        senTemps[i] = Sensor->getTempC(senAddress[i]);

    if (status.changeMode == notMode)
        Sensor->requestTemperatures();
}

void Thermometer::loop_DHT()
{
    float h, t;

    h = dht->readHumidity();
    t = dht->readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor.");
        return;
    }

    senTemps[0] = t;
    humidity = h;
}

void Thermometer::reBegin()
{
    status.mode = notMode;
    senNum = 0;

    if (dht) {
        delete dht;
        dht = NULL;
    }

    if (Sensor) {
        delete Sensor;
        Sensor = NULL;
    }

    switch (status.changeMode)
    {
    case ModeDHT:
        begin_DHT(status.reg2, status.reg1);
        break;

    case ModeDS18:
        begin_DS18(status.reg1);
        break;
    }

    status.changeMode = notMode;
}

void Thermometer::copyAddress(uint8_t* source, uint8_t* dest)
{
    int i = sizeof(DeviceAddress);

    while(i--) {
        *dest = *source;
        dest++; source++;
    }
}