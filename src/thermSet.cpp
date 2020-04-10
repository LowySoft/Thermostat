#include <EEPROM.h>
#include <thermSet.h>

///////////////
// Emulated Eeprom címek 

#define     eeprom_addrSSID     0   // SSID címe az eeprom-ban
#define     eeprom_sizeSSID     32  // SSID mérete
#define     eeprom_addrPass     32  // Jelszó címe az eeprom-ban
#define     eeprom_sizePass     64  // Jelszó mérete
#define     eeprom_addrID       96  // Termostat azonosító
#define     eeprom_sizeID       64  // Termosztát azonosító mérete
#define     eeprom_addrFlag1    160 // Jelzőflagek
#define     eeprom_sizeFlag1    1   // Jelzőflag mérete

#define      eeprom_size 161

uint8_t     m_Flag1;    // Flag1 tükör

classThermSet::classThermSet() {
}

classThermSet::~classThermSet() {
}

void classThermSet::begin() {
    EEPROM.begin(eeprom_size);
    char cID[10];

    String SSID = readString(eeprom_addrSSID, eeprom_sizeSSID);
    String Pass = readString(eeprom_addrPass, eeprom_sizePass);
    String ID   = readString(eeprom_addrID, eeprom_sizeID);

    if ((SSID.length() >= eeprom_sizeSSID) || (Pass.length() >= eeprom_sizePass)) {               // Érvénytelen adat
        clearData(eeprom_addrSSID, eeprom_sizeSSID);
        clearData(eeprom_addrPass, eeprom_sizePass);
        Serial.println("thermSet: WiFi SSID and Passworld data is invalid. Initialize eeprom area.");
    }

    if ((ID.length() >= eeprom_sizeID) || (ID.length() == 0)) {                                     // Érvénytelen adat, első indítás
    // Azonosító inicializálása
        clearData(eeprom_addrID, eeprom_sizeID);
        ID.clear();
        ID = thermostatDefId;
        sprintf(cID, "%X", ESP.getChipId());
        ID += "-" + String(cID);
        writeString(ID, eeprom_addrID, eeprom_sizeID);

    // Flagek inicializálása
        m_Flag1 = tsFlag_WiFi;      // WiFi bekapcsólva

        EEPROM.write(eeprom_addrFlag1, m_Flag1);
        EEPROM.commit();

        Serial.println("thermSet: Thermostat setting is not valid. Initialize settings data:");
        Serial.printf ("          ID = %s\n", ID.c_str());
        Serial.println("          WiFi on");
        Serial.println("          Heat index off");
    }

    m_Flag1 = EEPROM.read(eeprom_addrFlag1);
}

String classThermSet::getSSID() {
    return readString(eeprom_addrSSID, eeprom_sizeSSID);
}

void classThermSet::setSSID(String tStr) {
    return writeString(tStr, eeprom_addrSSID, eeprom_sizeSSID);
}

void classThermSet::setSSID(char* tStr) {
    String str = tStr;

    return writeString(str, eeprom_addrSSID, eeprom_sizeSSID);
}

String classThermSet::getPassworld() {
    return readString(eeprom_addrPass, eeprom_sizePass);
}

void classThermSet::setPassworld(String tStr) {
    return writeString(tStr, eeprom_addrPass, eeprom_sizePass);
}

void classThermSet::setPassworld(char* tStr) {
    String str = tStr;

    return writeString(str, eeprom_addrPass, eeprom_sizePass);
}

String classThermSet::getID() {
    return readString(eeprom_addrID, eeprom_sizeID);
}

String classThermSet::getHardwareID() {
//    String id;
    
    return String(String(ESP.getChipId(), HEX) + String("-thermostat"));
}

void classThermSet::setID(String tStr) {
    return writeString(tStr, eeprom_addrID, eeprom_sizeID);
}

void classThermSet::setID(char* tStr) {
    String str = tStr;

    return writeString(str, eeprom_addrID, eeprom_sizeID);
}

bool classThermSet::get(uint8_t flagBit) {
    if (m_Flag1 & flagBit)
        return true;
    
    return false;
}

void classThermSet::set(uint8_t flagBit, bool status) {
    if (status)
        m_Flag1 |= flagBit;
    else
        m_Flag1 &= ~flagBit;
    
    EEPROM.write(eeprom_addrFlag1, m_Flag1);
    EEPROM.commit();
}

//////////////////////////////
//
// Privát fügvények

void   classThermSet::clearData(uint16_t addr, uint8_t maxSize) {
    uint8_t i = 0;

    for(; i < maxSize; i++, addr++)
        EEPROM.write(addr, 0);

    EEPROM.commit();
}

String classThermSet::readString(uint16_t addr, uint8_t maxSize) {
    uint8_t i;
    char    c;
    String  value;

    value.clear();

    for(i = 0; i < maxSize; i++) {
        c = char(EEPROM.read(addr++));
        if (c == 0)
            break;
        value += c;
    }

    return value;
}

void classThermSet::writeString(String str, uint16_t addr, uint8_t maxSize) {
    uint8_t i = 0, size;

    if (maxSize > 0)
        maxSize--;

    size = min((uint8_t)str.length(), maxSize);

    for(; i < size; i++, addr++) {
        EEPROM.write(addr, str[i]);
    }

    EEPROM.write(addr, 0);
    EEPROM.commit();
}

classThermSet thermSet;