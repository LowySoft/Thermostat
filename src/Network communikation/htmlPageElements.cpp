#include <Arduino.h>
#include "Network communikation/htmlPageElements.h"

namespace htmlPageElements {

    //********************************************************
    //   Fejléc elemek

    void globalCSS(String &content) {
        content += ".tg  {border-collapse:collapse;border-spacing:0;border-color:#bbb;margin:0px auto;}";
        content += ".tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 4px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#bbb;color:#594F4F;background-color:#E0FFEB;}";
        content += ".tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 4px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#bbb;color:#493F3F;background-color:#9DE0AD;}";
        content += ".tg .tg-996f{background-color:#C2FFD6;border-color:inherit;text-align:center;vertical-align:top}";
        content += ".tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}";
        content += ".tg .tg-nref{background-color:#C2FFD6;border-color:inherit;text-align:center;vertical-align:middle}";
//        content += "@media screen and (max-width: 767px) {.tg {width: auto !important;}.tg col {width: auto !important;}.tg-wrap {overflow-x: auto;-webkit-overflow-scrolling: touch;margin: auto 0px;}}";
        content += "body {";
        content +=     "background-color:#5f9ea0";
        content += "}";
        content += "form {";
        content +=     "display: grid;";
        content +=     "place-items: center;";
        content +=     "}";
        content += ".Button {";
        content +=     "box-shadow: 0px 10px 14px -7px #3e7327;";
        content +=     "background:linear-gradient(to bottom, #77b55a 5%, #72b352 100%);";
        content +=     "background-color:#77b55a;";
        content +=     "border-radius:10px;";
        content +=     "border:2px solid #4b8f29;";
        content +=     "display:inline-block;";
        content +=     "cursor:pointer;";
        content +=     "color:#ffffff;";
        content +=     "font-family:Arial;";
        content +=     "font-size:100%;";
        content +=     "font-weight:bold;";
        content +=     "padding:6px 12px;";
        content +=     "text-decoration:none;";
        content +=     "text-shadow:0px 1px 0px #5b8a3c;";
        content += "}";
        content += ".Button:hover {";
        content +=     "background:linear-gradient(to bottom, #72b352 5%, #77b55a 100%);";
        content +=     "background-color:#72b352;";
        content += "}";
        content += ".Button:active {";
        content +=     "position:relative;";
        content +=     "top:1px;";
        content += "}";
        content += ".LowySwitchButton {";
        content +=     "margin: 5px;";
        content +=     "border:0px;";
        content +=     "padding:4px;";
        content +=     "border-radius: 40px;";
        content +=     "width: 72px;";
        content +=     "height: 18px;";
        content +=     "background-color:lightsalmon;";
        content +=     "vertical-align: middle;";
        content += "}";
    }


    void HTML_Header(String &content, bool refresh) {
        content += "<!DOCTYPE html>";
        content += "<html lang='HU'>";
        content += "<head>";
        content +=    "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'></meta>";
        content +=    "<meta name='author' content='LowySoft' />";
        content +=    "<meta name='copyright' content='LowySoft' />";
        content +=    "<meta name='description' content='LowySoft thermostat setting paga' />";
        content +=    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        if (refresh)
            content += "<meta http-equiv='refresh' content='20'>";
        content +=    "<title>LowySoft Termostat</title>";
        content +=    "<style>";
        globalCSS(content);
        content +=    "</style>";
        content +=    "<script type='text/javascript'>";
    }

    void HTML_Loaded(String tID, String &content) {
        content += "function loaded()";
        content += "{";
        content +=    "document.getElementById('TermostatID').innerHTML = '";
        content +=     tID;
        content +=  "';";
    }

    void HTML_LoadedEnd(String &content) {
        content += "}";
    }

    void HTML_HeaderEnd(String &content) {
        content +=    "</script>";
        content += "</head>"; 
    }

    void HTML_createLowySwitchButton_JS(String &content) {
        content += "function createLowySwitchButton(bTitle, bName, bAppend)";
        content += "{";
        content +=      "var b_Title = document.createTextNode(bTitle);";
        content +=      "var newButton = document.createElement('canvas');";
        content +=      "var newHidden = document.createElement('input');";
       content +=      "var newDiv = document.createElement('div');";

        content +=      "newButton.id = bName;";
        content +=      "newButton.className = 'LowySwitchButton';";
        content +=      "newButton.addEventListener('click', function(){drawLowySwitchButton(bName, 3);});";
	
        content +=      "newHidden.type = 'hidden';";
        content +=      "newHidden.name = bName;";
	
        content +=      "var parent = document.getElementById(bAppend);";
        content +=      "parent.appendChild(newDiv);";
        content +=      "newDiv.appendChild(b_Title);";
        content +=      "newDiv.appendChild(newButton);";
        content +=      "newDiv.appendChild(newHidden);";
        content += "}";
    }

    void HTML_LowySwitchButtonTabe(String &content) {
        content += "<table border id='LSB_Table' align='center'></table>";
    }

    void HTML_addLowySwitchButtonToTheTable_JS(String &content) {
        content += "function addLowySwitchButtonToTheTable(bTitle, bName)";
        content += "{";
        content +=      "var newLabel = document.createElement('label');";
        content +=      "var newButton = document.createElement('canvas');";
        content +=      "var newHidden = document.createElement('input');";

        content +=      "newLabel.innerHTML=bTitle;";

        content +=      "newButton.id = bName;";
        content +=      "newButton.className = 'LowySwitchButton';";
        content +=      "newButton.addEventListener('click', function(){drawLowySwitchButton(bName, 3);});";
	
        content +=      "newHidden.type = 'hidden';";
        content +=      "newHidden.name = bName;";

        content +=      "var newRow   = document.createElement('tr');";
        content +=      "var newCell1 = document.createElement('td');";
        content +=      "var newCell2 = document.createElement('td');";

        content +=      "newRow.appendChild(newCell1);";
        content +=      "newRow.appendChild(newCell2);";

        content +=      "var parent = document.getElementById('LSB_Table');";
        content +=      "parent.appendChild(newRow);";

        content +=      "newCell1.appendChild(newLabel);";

        content +=      "newCell2.appendChild(newButton);";
        content +=      "newCell2.appendChild(newHidden);";
        content += "}";
    }

    void HTML_drawLowySwitchButton_JS(String &content) {
        content += "function drawLowySwitchButton(name, revers) {";
        content +=      "var vaszon   = document.getElementById(name);";
        content +=      "var kapcsolo = document.getElementsByName(name)[0].value;";
        content +=      "var ctx = vaszon.getContext('2d');";
        content +=      "var pozX;";

        content +=      "vaszon.width = 72;";
        content +=      "vaszon.height = 18;";

        content +=      "if (revers == 3) {";
        content +=          "if (kapcsolo == 0) {";
        content +=              "kapcsolo = 1;";
        content +=          "} else {";
        content +=              "kapcsolo = 0;}";
        content +=      "} else {";
        content +=          "kapcsolo = revers;";
        content +=      "}";
	
        content +=      "document.getElementsByName(name)[0].value = kapcsolo;";
	
        content +=      "ctx.beginPath();";
        content +=      "ctx.font = '16px Arial';";
        content +=      "if ( kapcsolo == 0) {";
        content +=          "ctx.fillStyle='rgb(255,0,0)';";
        content +=          "ctx.fillText('Ki', 26, 15);";
        content +=          "ctx.fillStyle='rgb(255,80,80)';";
        content +=          "pozX = 12;";
        content +=      "} else {";
        content +=          "ctx.fillStyle='rgb(0,120,0)';";
        content +=          "ctx.fillText('Be', 26, 15);";
        content +=          "ctx.fillStyle='rgb(80,150,80)';";
        content +=          "pozX = 59;";
        content +=      "}";
        content +=      "ctx.arc(pozX, 9, 8, 0, 2 * Math.PI);";
        content +=      "ctx.fill();";
        content +=      "ctx.stroke();";
        content += "}";
    }

    //******************************************************
    // Törzs elemek

    void HTML_Body(String siteTitle, String &content) {
        content += "<body onload='loaded();'>";
        content += "<p><h1 style='text-align: center;'>LowySoft Termosztát</h1></p>";
        content += "<h2 style='text-align: center; line-height: 0%;'><label id='TermostatID'></label></h2>";
        content += "<h3 style='text-align: center;'>";
        content += siteTitle;
        content += "</h3>";
    }

    void HTML_BodyEnd(String &content) {
        content += "<br/>";
        content += "<div style='position: relative;'>";
        content +=      "<h6 style='position: fixed; bottom: 0; width:100%; left: 20px;'>";
        content +=      "LowySost Termostat (C) 2020 V: 0.02.0000<br/>";
        content +=      "LowySoft Termostat Web Meneger (C) 2020 V: 1.00.000";
        content +=     "</h6>";
        content += "</div>";
        content += "</body>";
        content += "</html>";
    }

    //*******************************************************
    // Főoldal

    void HTML_Root(String &content) {
        content += "<form>";
        content +=     "<fieldset style='text-align:center'>";
        content +=         "<legend>&nbsp;Menü&nbsp;</legend>";
        content +=         "<br/>";
        content +=         "<input type='submit' class='Button' formaction='./thermal.html'   value='Hőfokok beállítása' style='font-size: 100%;'/><br/>";
        content +=         "<input type='submit' class='Button' formaction='./settings.html'  value='Általános beállítások' style='font-size: 100%;'/><br/>";
        content +=         "<input type='submit' class='Button' formaction='./ap_select.html' value='Hálózat beállítás' style='font-size: 100%;'/><br/>";
        content +=         "<br/>";
        content +=     "</fieldset>";
        content += "</form>";
    }

    //*******************************************************
    // Hállózatbeállítások (AP Select)

    void HTML_ApSelect_JS(String &content) {
        content += "var hatterSz;";
        content += "var tcPass;";
        content += "var tcSSID;";

        content +=  "function setTextBoxEnables(numb) {";

        content +=     "var ep = document.getElementsByName('APList')[numb].getAttributeNode('ePass').value;";
        content +=     "var es = document.getElementsByName('APList')[numb].getAttributeNode('eSSID').value;";

        content +=     "if (ep == 1) {";
        content +=         "tcPass.disabled = false;";
        content +=         "tcPass.style.backgroundColor = hatterSz;"; 
        content +=     "}";
        content +=     "else {";
        content +=         "tcPass.disabled = true;";
        content +=         "tcPass.style.backgroundColor = '#606060';";
        content +=     "}";

        content +=     "if (es == 1) {";
        content +=         "tcSSID.disabled = false;";
        content +=         "tcSSID.style.backgroundColor = hatterSz;";
        content +=     "}";
        content +=     "else {";
        content +=         "tcSSID.disabled = true;";
        content +=         "tcSSID.style.backgroundColor = '#606060';";
        content +=     "}";

        content +=     "return;";
        content +=  "}";
    }

    void HTML_ApSelect_SelectAp_JS(String &content) {
        content +=  "function selectAP(num) {";
        content +=      "document.getElementsByName('APList')[num].checked = true;";
        content +=      "setTextBoxEnables(num);";
        content +=  "}";
    }

    void HTML_ApSelect_Loaded(uint8_t selAP, String &content) {
        content += "hatterSz = document.getElementById('Passworld').style.backgroundColor;";
        content += "tcPass = document.getElementById('Passworld');";
        content += "tcSSID = document.getElementById('SSID');";

        content += "selectAP(";
        content += String(selAP);
        content += ");";
        content += "tcPass.style.fontSize = '80%';";
        content += "tcSSID.style.fontSize = '80%';";
    }

    void HTML_ApSelectStart(String &content) {
        content += "<form action='ap_save_selectAP'>";
        content +=  "<fieldset>";
        content +=      "<legend>&nbsp;Válasszon hálózatot&nbsp;</legend>";
    }

    void HTML_ApSelectEnd(String &content) {
        content +=        "<table>";
        content +=            "<tr>";
        content +=                "<td style='text-align: right;'>SSID:</td>";
        content +=                "<td><input type='text' name='SSID' id='SSID' maxlength='32'/></td>";
        content +=            "</tr>";
        content +=            "<tr>";
        content +=                "<td style='text-align: right;'>Jelszó:</td>";
        content +=                "<td><input type='text' name='Passworld' id='Passworld' maxlength='64'><br/></td>";
        content +=            "</tr>";
        content +=        "</table>";
        content +=    "</fieldset>";
        content +=    "<p><input type='button' class='Button' onClick='document.location.href=\"/\";' value='Vissza'/>";
        content +=    "<input type='submit' class='Button' value='Mentés' /></p>";
        content +="</form>";                                                                                         
    }

    //***************************************************
    //
    //   Beállítások lap

}