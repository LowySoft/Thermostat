#include <ESP8266WebServer.h>
#include "Network communikation/htmlPages.h"
#include "thermSet.h"

extern ESP8266WebServer server;

namespace htmlPages {

    String  content;    // Ebbe a stringbe készűl a weblap
    uint8_t maxAp;      // Elérhető hállózatok száma

    void createRoot() {
      String ID = thermSet.getID();

      content.clear();
      htmlPageElements::HTML_Header(content);
      htmlPageElements::HTML_Loaded(ID, content);
      htmlPageElements::HTML_LoadedEnd(content);
      htmlPageElements::HTML_HeaderEnd(content);
      htmlPageElements::HTML_Body("Főmenü", content);
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
      } else {
          content += "<p style='text-align: center; color: red;'>Hibás paraméterlista!<br/>A mentés nem sikerűlt.</p>";
      }

      content += "<p style='text-align:center'>";
      content += "<input type='button' class='Button' onClick='document.location.href=\"/\";' value='Vissza'/>";
      content += "</p>";
      htmlPageElements::HTML_BodyEnd(content);

      server.send(200, "text/html", content);

    }
}
