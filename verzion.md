#        Termostat 
LowySoft 2020 (C)

## Szükséges könyvtárak:

U8G2  -  Kijelző driver library

OneWire - 1 wire busz vezérlő library a Dallas szenzorokhoz

DallasTemperature - Dallas hőmérő szenzorok library

DHT Sensor Library - DHT hőmérséglet és párataltarom mérő szenzor library

Adafruit Unified Sensor - A DHT szenzor library működéséhez szükséges library


## *Fejlesztés követése:*

**2020. Március 1**
- Hállozati kommunikáció a Connect osztályba szervezve
- Beállítások a thermSet osztályba kerűltek, mely a flesh memóriában tárólja őket
- http://thermostat.local címen kersztüli kapcsolódás mDNS segítségével
- Beállításhoz weblapok létrehozva:
   - Főoldal
   - Hálózati beállítások

**2020. Január 22**
- Kezeli SH1106 chippel szerelt 128*64-es felbontású kijelzőt
- Kezeli a Dallas Semiconductor DS18 sorozatú hőmérő szenzorait
- Kezeli a DHT1x, DHT2x sorozatú hőmérséglet és páratartalom mérő modulokat
- Csatlakozik a WiFi routerhez

Készűlt a [VsCode](https://code.visualstudio.com) alkalmazás, [PlatformIO](https://www.platformio.org/) kiterjesztésének segítségével.
