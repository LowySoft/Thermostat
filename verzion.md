# Termostat

LowySoft 2020 (C)

## Szükséges könyvtárak

- U8G2  -  Kijelző driver library
- OneWire - 1 wire busz vezérlő library a Dallas szenzorokhoz
- DallasTemperature - Dallas hőmérő szenzorok library
- DHT Sensor Library - DHT hőmérséglet és párataltarom mérő szenzor library
- Adafruit Unified Sensor - A DHT szenzor library működéséhez szükséges library

## *Fejlesztés követése:*

### **2020. Április 10**

- Kapcsolódási protokól módosítása védett SSL protokólra. Saját binztonsági kulcs létrehozására
  ajánlott az openSSL, a következő parancsal:
  > req -x509 -newkey rsa:1024 -sha256 -keyout key.txt -out cert.txt -nodes -days 36500 -subj "/C=HU/ST=./L=./O=cégnév/OU=szerkezeti egység/CN=webcím" -addext subjectAltName=DNS:webcím
- http hívás átirányítása https oldalra, SSL-el titkosított kapcsolat esetén.
- A titkosított átvitel ki/bekapcsólható fórdítás előtt a pratformio.ini fájlban.
- OLED kijelző használata tíltható a patformio.ini fájlban.
- OLED funkciók bekerűltek a displayClass osztályba.
- Webfelületen megjelent a Beállítások lap, ahól ki lehet kapcsólni a WiFi egységet és a hőérzet alapú vezérlést, valamint be lehet állítani a termosztát egyedi azonosítóját.
  
### **2020. Március 11**

- Hálózati funkciók áthelyezve a 'Network communikation' mappába
- Weblapokat felépítő kód a könnyebb olvasás és érthetőség kedvéért átszervezve.
- mDNS cím megváltoztatása http://xxxxxx-thermostat.local -ra
- Termosztát hálózati azonosítójának megváltoztatása xxxxxx-thermostat-ra

xxxxxx = Chip egyedi sorszáma

### **2020. Március 1**

- Hállozati kommunikáció a Connect osztályba szervezve
- Beállítások a thermSet osztályba kerűltek, mely a flesh memóriában tárólja őket
- http://thermostat.local címen kersztüli kapcsolódás mDNS segítségével
- Beállításhoz weblapok létrehozva:
  - Főoldal
  - Hálózati beállítások

### **2020. Január 22**

- Kezeli SH1106 chippel szerelt 128*64-es felbontású kijelzőt
- Kezeli a Dallas Semiconductor DS18 sorozatú hőmérő szenzorait
- Kezeli a DHT1x, DHT2x sorozatú hőmérséglet és páratartalom mérő modulokat
- Csatlakozik a WiFi routerhez

Készűlt a [VsCode](https://code.visualstudio.com) alkalmazás, [PlatformIO](https://www.platformio.org/) kiterjesztésének segítségével.
