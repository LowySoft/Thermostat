#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "thermSet.h"
#include "Network communikation/connect.h"
#include "Network communikation/htmlPages.h"

ESP8266WebServer server(80);
//uint8_t maxAp;                  // Last network scan found network number

Connect::Connect()
{
    mode = notConnect;
}

Connect::~Connect()
{
    WiFi.disconnect();
}

// Connect to WiFi
boolean Connect::begin()
{
    uint8_t i;

    WiFi.disconnect();
    if (thermSet.getSSID().length() == 0)               // Ha nincs SSID beállítva
        return false;

    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.hostname(thermSet.getHardwareID());
    WiFi.begin(thermSet.getSSID().c_str(), thermSet.getPassworld().c_str());
    Serial.printf("Connect: Connecting to '%s' network", thermSet.getSSID().c_str());

    i = 0;
    while ((WiFi.status() != WL_CONNECTED) && (i++ < 16))
    {
        delay(1000);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(" failed.");
        return false;
    }

    Serial.println(" done.");
    Serial.printf("      IP=%s\n", WiFi.localIP().toString().c_str());
    mode &= ~modeAP;
    mode |= modeClient;
    return true;
}

// Start WiFi AP mode
boolean Connect::beginAP() {
    IPAddress ap_static_ip, ap_static_gw, ap_static_sn;
    bool statAP = false;

    ap_static_ip.fromString("192.168.1.1");
    ap_static_gw.fromString("192.168.1.254");
    ap_static_sn.fromString("255.255.255.0");

    if (WiFi.mode(WIFI_AP))    // Átváltás AP módba
    {
        WiFi.disconnect();
        delay(100);

        if (WiFi.softAPConfig(ap_static_ip, ap_static_gw, ap_static_sn))
            if (WiFi.softAP(AP_SSID, AP_PASS, 2))
                statAP = true;
    }

    if (statAP) {
        IPAddress APIP = WiFi.softAPIP();
        Serial.print("Connect: Start AP mode\n    SSID="); Serial.println(AP_SSID);
        Serial.print("      IP="); Serial.println(APIP.toString());
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
    createWebServer();
    server.begin();

    Serial.println("Connect:  Web server is runing.");
}

void Connect::begin_mDNS() {
  if (!MDNS.begin(thermSet.getHardwareID()))
    Serial.println("Connect: mDNS not started!");
  else {
    MDNS.addService("http", "tcp", 80);
    Serial.printf("Connect: mDNS started, domain: %s.local\n", thermSet.getHardwareID().c_str());
    mode |= modeRunmDNS;
  }
}

void Connect::loop()
{
    if (mode & modeRunmDNS)
        MDNS.update();

    if (mode & modeRunServer) {
        server.handleClient();
    }
}

////////////////////////
//
// Private section

//String content;

void Connect::createWebServer()
{
    // Főoldal
/*    server.on("/", []() {
      String ID = thermSet.getID();

      content.clear();
      HTML_Header()
      HTML_Loaded(ID)
      HTML_LoadedEnd()
      HTML_HeaderEnd()
      HTML_Body("Főmenü")
      HTML_Root
      HTML_BodyEnd
     
      server.send(200, "text/html", content);
    });
*/
    server.on("/", htmlPages::createRoot);

    // Hállózatválasztás
    /*server.on("/ap_select.html", []() {
        int8_t selAp = -1;
        uint8_t aktAp = 0;
        String ID = thermSet.getID();
        WiFi.scanDelete();
        maxAp = WiFi.scanNetworks();

      // Aktuális AP megkeresése
      for(aktAp = 0; aktAp < maxAp; aktAp++) {
          if (WiFi.SSID(aktAp) == thermSet.getSSID())
            selAp = aktAp;
      }

      if (selAp == -1) {
          if (thermSet.getSSID().length() > 0) {
              selAp = maxAp;
          } else {
          selAp = 0;
          }
      }

      content.clear();
      HTML_Header();
      HTML_ApSelect_JS()
      HTML_ApSelect_SelectAp_JS()
      HTML_Loaded(thermSet.getID())
      HTML_ApSelect_Loaded(selAp)
      if (selAp == maxAp) 
          content += "tcSSID.value = '" + thermSet.getSSID() + "';";
      if ( WiFi.encryptionType(selAp) != ENC_TYPE_NONE)
          content += "tcPass.value = '" + thermSet.getPassworld() + "';";
      HTML_LoadedEnd()
      HTML_HeaderEnd()

      HTML_Body("Hálózati beállítások")
      HTML_ApSelectStart()

      for (aktAp = 0; aktAp < maxAp; aktAp++) {
        content += "<input type='radio' name='APList' id='APList_"; content += String(aktAp);
        content += "' ePass=";
        content += WiFi.encryptionType(aktAp) == ENC_TYPE_NONE ? 0 : 1;         // Jelszó mező engedélyezése, ha szükséges
        content += " eSSID=0";
        content += " value='"; content += String(aktAp);
        content += "' onclick='setTextBoxEnables("; content += String(aktAp);
        content += ");";
        content += "'/><label for='APList_"; content += String(aktAp);
        content += "'>" + WiFi.SSID(aktAp) + " (" + WiFi.RSSI(aktAp) + " dBm)";
        content += "</label><br/>";
      }

      content += "<br/>";
      content += "<input type='radio' name='APList' id='APList_"; content += String(aktAp);
      content += "' ePass=1 eSSID=1";
      content += " value='"; content += String(aktAp);
      content += "' onclick='setTextBoxEnables(" + String(aktAp) +  ");'/><label for='APList_"; content += String(aktAp);
      content += "'>Kézi bevitel:</label><br/>";

      HTML_ApSelectEnd()
      HTML_BodyEnd
      
      server.send(200, "text/html", content);

    });
    */
    server.on("/ap_select.html", htmlPages::createAPSelect);

    // Hállózat adatainak mentése
/*    server.on("/ap_save_selectAP", HTTP_GET, []() {
      String ID = thermSet.getID();
      String pSSID;
      String pPassw;
      uint8_t listId = 0;
      boolean error = false;

      if (server.hasArg("APList")) {
          listId = server.arg("APList").toInt();
          if (listId == maxAp)
            pSSID = server.arg("SSID");
          else
            pSSID = WiFi.SSID(listId);
          
          pPassw.clear();
          if (server.hasArg("Passworld"))
            pPassw = server.arg("Passworld");

      } else {
          error = true;
      }

      content.clear();
      HTML_Header()
      HTML_Loaded(ID)
      HTML_LoadedEnd()
      HTML_HeaderEnd()
      HTML_Body("AP Beállítások mentése")

      if (error == false) {
          thermSet.setSSID(pSSID.c_str());
          thermSet.setPassworld(pPassw);

          content += "<p style='text-align: center; color: green;'>";
          content += "Az adatok sikeressen el lettek mentve:<br/><br/>";
          content += "SSID: " + pSSID + "<br/>";
          content += "Passworld: " + pPassw + "<br/>";
          content += "</p>";
      } else {
          content += "<p style='text-align: center; color: red;'>Hibás paraméterlista!<br/>A mentés nem sikerűlt.</p>";
      }

      content += "<p style='text-align:center'>";
      content += "<input type='button' class='Button' onClick='document.location.href=\"/\";' value='Vissza'/>";
      content += "</p>";
      HTML_BodyEnd

      server.send(200, "text/html", content);

    });
*/
    server.on("/ap_save_selectAP", HTTP_GET, htmlPages::saveAPSelect);
}
