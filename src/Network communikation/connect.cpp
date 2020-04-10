#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include "thermSet.h"
#include "Network communikation/connect.h"
#include "Network communikation/htmlPages.h"
#include "Network communikation/secureKeys.h"

#define DNSPort 53

#ifdef _SecServer_
BearSSL::ESP8266WebServerSecure server(443);
ESP8266WebServer                serverHTTP(80);
#else
ESP8266WebServer                server(80);
#endif

DNSServer dnsServer;

Connect::Connect()
{
    mode = notConnect;
}

Connect::~Connect()
{
    off();
    WiFi.disconnect();
}

// Connect to WiFi
boolean Connect::begin()
{
    uint8_t i;

    WiFi.disconnect();
    dnsServer.stop();

    if (thermSet.getSSID().length() == 0)               // Ha nincs SSID beállítva
        return false;

    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.hostname(thermSet.getHardwareID());
    WiFi.begin(thermSet.getSSID().c_str(), thermSet.getPassworld().c_str());
    Serial.printf("Connect: Connecting to '%s' network", thermSet.getSSID().c_str());

    i = 0;
    while ((WiFi.status() != WL_CONNECTED) && (i++ < 10))
    {
        delay(1000);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(" failed.");
        return false;
    }

    Serial.println(" done.");
    Serial.printf("         IP=%s\n", WiFi.localIP().toString().c_str());
    mode &= ~modeAP;
    mode |= modeClient;

    return true;
}

// Start WiFi AP mode
boolean Connect::beginAP() {
    IPAddress ap_static_ip, ap_static_gw, ap_static_sn;
    bool statAP = false;

    ap_static_ip.fromString("192.168.1.1");
    ap_static_sn.fromString("255.255.255.0");

    if (WiFi.mode(WIFI_AP))    // Átváltás AP módba
    {
        WiFi.disconnect();
        delay(100);

        if (WiFi.softAPConfig(ap_static_ip, ap_static_ip, ap_static_sn))
            if (WiFi.softAP(AP_SSID, AP_PASS, 2)) {
                dnsServer.start(DNSPort, "thermostat.local", ap_static_ip);
                statAP = true;
            }
    }

    if (statAP) {
        IPAddress APIP = WiFi.softAPIP();
        Serial.print("Connect: Start AP mode\n    SSID="); Serial.println(AP_SSID);
        Serial.print("         IP="); Serial.print(APIP.toString());
        Serial.println("  DNS: thermostat.local");
        mode &= ~modeClient;
        mode |= modeAP;
    } else {
        Serial.println("Connect: AP mode not started!");
    }

    return statAP;
}

// Start AP, create Web server.
void Connect::beginServer()
{
    // Create Web server.
    mode |= modeRunServer;

#ifdef _SecServer_
    server.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));

    if (mode & modeAP) {    
        serverHTTP.on("/", [](){
            serverHTTP.sendHeader("Location", "https://thermostat.local", true);
            serverHTTP.send(301, "text/plain", "");
        });
    }

    if (mode & modeClient) {
        serverHTTP.on("/", [](){
            String str;

            str = "https://" + thermSet.getHardwareID() + ".local";
            serverHTTP.sendHeader("Location", str, true);
            serverHTTP.send(301, "text/plain", "");
        });
    }

    serverHTTP.begin();
#endif

    createWebServer();
    server.begin();

#ifdef _SecServer_
    Serial.println("Connect: Secure Web server is runing.");
#else
    Serial.println("Connect: Web server is runing.");
#endif
}

void Connect::begin_mDNS() {
  if (!MDNS.begin(thermSet.getHardwareID()))
    Serial.println("Connect: mDNS not started!");
  else {
    Serial.printf("Connect: mDNS started, domain: %s.local\n", thermSet.getHardwareID().c_str());
    mode |= modeRunmDNS;
  }
}

void Connect::off()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);

    server.stop();
#ifdef _SecServer_
    serverHTTP.stop();
#endif
    MDNS.end();
    dnsServer.stop();

    mode = notConnect;
}

void Connect::loop()
{
    if (mode & modeRunmDNS)
        MDNS.update();

    if (mode & modeRunServer) {
#ifdef _SecServer_
        serverHTTP.handleClient();
#endif
        server.handleClient();
    }

    if (mode & modeAP) {
        dnsServer.processNextRequest();
    }
}

boolean Connect::isAPmode() {
    return (mode & modeAP) ? true : false;
}

////////////////////////
//
// Private section

void Connect::createWebServer()
{
    // Főoldal
    server.on("/", htmlPages::createRoot);

    // Hállózatválasztás
    server.on("/ap_select.html", htmlPages::createAPSelect);

    // Hállózat adatainak mentése
    server.on("/ap_save_selectAP", HTTP_GET, htmlPages::saveAPSelect);

    // Beállítások lap
    server.on("/settings.html", htmlPages::createSettings);

    // Beállítások mentése
    server.on("/save_settings", HTTP_POST, htmlPages::saveSettings);
    
}
