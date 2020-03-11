# Termostat

LowySoft 2020 (C)

## Szükséges könyvtárak

- U8G2  -  Kijelző driver library,
- OneWire - 1 wire busz vezérlő library,
- DallasTemperature - Dallas hőmérő szenzorok library,
- DHT Sensor Library - DHT hőmérséglet és párataltarom mérő szenzor library,
- Adafruit Unified Sensor - A DHT szenzor library működéséhez szükséges library

## *Tulajdonságok:*

- http://xxxxxx-thermostat.local címen kersztüli kapcsolódás a helyi hállózaton
- Egység hállózati neve xxxxxx-thermostat
- AP módon keresztüli beállítása a wifi kapcsolatnak

xxxxxx = A termosztátban található chip egyedi azonosítója

### **2020. Január 22**

- Hőmérséklet és páratartalom mérése
- Csatlakozik a WiFi routerhez

Készűlt a [VsCode](https://code.visualstudio.com) alkalmazás, [PlatformIO](https://www.platformio.org/) kiterjesztésének segítségével.
