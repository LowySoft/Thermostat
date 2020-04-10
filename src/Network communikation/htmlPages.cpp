#include <ESP8266WebServerSecure.h>
#include "Network communikation/htmlPages.h"
#include "Network communikation/htmlPageElements.h"
#include "thermSet.h"
#include "Thermometer.h"

#ifdef _SecServer_
extern ESP8266WebServerSecure server;
#else
extern ESP8266WebServer       server;
#endif

extern Thermometer sensors;

namespace htmlPages {

    String  content;    // Ebbe a stringbe készűl a weblap
    uint8_t maxAp;      // Elérhető hállózatok száma

    void createRoot() {
      String ID = thermSet.getID();

      content.clear();
      htmlPageElements::HTML_Header(content, true);
      htmlPageElements::HTML_Loaded(ID, content);
      htmlPageElements::HTML_LoadedEnd(content);
      htmlPageElements::HTML_HeaderEnd(content);
      htmlPageElements::HTML_Body("Főoldal", content);
      content += "<h3 style='text-align: center;'>";
      content += "Hőfok: ";
      content += String(sensors.getThemp(), 1) + " °C<br>";
      
      if (sensors.isHumidity()) {
        content += "Páratartalom: ";
        content += String(sensors.getHumidity(), 1) + "%<br>";
        content += "Hőérzet: ";
        content += String(sensors.getHeatIndex() , 1) + " °C<br>";
      }

      content += "</h3>";
      htmlPageElements::HTML_Root(content);
      htmlPageElements::HTML_BodyEnd(content);

      server.send(200, "text/html", content);
    }

    void createAPSelect() {
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
      htmlPageElements::HTML_Header(content);
      htmlPageElements::HTML_ApSelect_JS(content);
      htmlPageElements::HTML_ApSelect_SelectAp_JS(content);
      htmlPageElements::HTML_Loaded(thermSet.getID(), content);
      htmlPageElements::HTML_ApSelect_Loaded(selAp, content);
      if (selAp == maxAp) 
          content += "tcSSID.value = '" + thermSet.getSSID() + "';";
      if ( WiFi.encryptionType(selAp) != ENC_TYPE_NONE)
          content += "tcPass.value = '" + thermSet.getPassworld() + "';";
      htmlPageElements::HTML_LoadedEnd(content);
      htmlPageElements::HTML_HeaderEnd(content);

      htmlPageElements::HTML_Body("Hálózati beállítások", content);
      htmlPageElements::HTML_ApSelectStart(content);

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

      htmlPageElements::HTML_ApSelectEnd(content);
      htmlPageElements::HTML_BodyEnd(content);

      server.send(200, "text/html", content);
    }

    void saveAPSelect() {
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
      htmlPageElements::HTML_Header(content);
      htmlPageElements::HTML_Loaded(ID, content);
      htmlPageElements::HTML_LoadedEnd(content);
      htmlPageElements::HTML_HeaderEnd(content);
      htmlPageElements::HTML_Body("AP Beállítások mentése", content);

      if (error == false) {
          thermSet.setSSID(pSSID.c_str());
          thermSet.setPassworld(pPassw);

          content += "<p style='text-align: center; color: green;'>";
          content += "Az adatok sikeressen el lettek mentve:<br/><br/>";
          content += "SSID: " + pSSID + "<br/>";
          content += "Passworld: " + pPassw + "<br/>";
          content += "</p>";
          content += "<p style='text-align:center'>";
          content += "Az eszköz újraindúl.";
          content += "</p>";
      } else {
          content += "<p style='text-align: center; color: red;'>Hibás paraméterlista!<br/>A mentés nem sikerűlt.</p>";
          content += "<p style='text-align:center'>";
          content += "<input type='button' class='Button' onClick='document.location.href=\"/\";' value='Vissza'/>";
          content += "</p>";
      }

      htmlPageElements::HTML_BodyEnd(content);
      
      server.send(200, "text/html", content);
      if (error == false)
        ESP.restart();
    }

    void createSettings() {
      content.clear();
      htmlPageElements::HTML_Header(content);
      htmlPageElements::HTML_addLowySwitchButtonToTheTable_JS(content);
      htmlPageElements::HTML_drawLowySwitchButton_JS(content);
      htmlPageElements::HTML_Loaded(thermSet.getID(), content);

      content += "drawLowySwitchButton('wifi'," + String(isWiFiEnable) + ");";
      if (sensors.isHumidity())   // Ha van páratartalom mérés
        content += "drawLowySwitchButton('heat'," + String(isHeatIndexEnable) + ");";
      
      htmlPageElements::HTML_LoadedEnd(content);
      htmlPageElements::HTML_HeaderEnd(content);

      htmlPageElements::HTML_Body("Beállítások", content);
      content += "<form method='POST' action='save_settings'>";
      htmlPageElements::HTML_LowySwitchButtonTabe(content);
      content += "<p align='center'>";
      content += "<input type='button' class='Button' value='Vissza' onClick='document.location.href=\"/\";'>";
      content += "<input type='submit' class='Button' value='Mentés'>";
      content += "</p>";
      content += "</form>";

      if (sensors.isHumidity())   // Ha van páratartalom mérés
        content += "<br><div align='center'> <sup>*</sup> A hőérzet a mért hőmérséglet és a páratartalom alapján kerűl megállapításra.</div>";

      content += "<script>";
      content += "addLowySwitchButtonToTheTable('WiFi:', 'wifi');";
      if (sensors.isHumidity())   // Ha van páratartalom mérés
        content += "addLowySwitchButtonToTheTable('<sup>*</sup> Hőérzet alapú használat:', 'heat');";

      // Azonosító sor hozzáadása a táblázathoz
      content +=      "var newRow   = document.createElement('tr');";
      content +=      "var newCell1 = document.createElement('td');";
      content +=      "var newCell2 = document.createElement('td');";

      content +=      "newRow.appendChild(newCell1);";
      content +=      "newRow.appendChild(newCell2);";

      content +=      "var parent = document.getElementById('LSB_Table');";
      content +=      "parent.appendChild(newRow);";

      content += "newCell1.innerHTML='Azonosító:';";

      content += "var newInput = document.createElement('input');";
      content += "newInput.type='text';";
      content += "newInput.maxSize=64;";
      content += "newInput.style.margin = 5;";
      content += "newInput.value='" + thermSet.getID() + "';";
      content += "newInput.name='thermID';";

      content += "newCell2.appendChild(newInput);";
      content += "</script>";
      
      htmlPageElements::HTML_BodyEnd(content);

      server.send(200, "text/html", content);
    }

    void saveSettings() {
      long param;

      if (server.hasArg("wifi")) {
        param = server.arg("wifi").toInt();
        if (param == 0) WiFi_Disable;
         else WiFi_Enable;
      }

      if(server.hasArg("heat")) {
        param = server.arg("heat").toInt();
        if (param == 0) HeatIndex_Disable;
         else HeatIndex_Enable;
      }

      if(server.hasArg("thermID"))
        thermSet.setID(server.arg("thermID"));

      server.sendHeader("Location", "/", true);
      server.send(301, "text/plain", "");
    }
}