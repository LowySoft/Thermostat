#ifndef HTML_DEF_H
#define HTML_DEF_H

#define globalCSS()                                                                                                                                                                                                         \
content += ".tg  {border-collapse:collapse;border-spacing:0;border-color:#bbb;margin:0px auto;}";                                                                                                                                         \
content += ".tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 4px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#bbb;color:#594F4F;background-color:#E0FFEB;}";                       \
content += ".tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 4px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#bbb;color:#493F3F;background-color:#9DE0AD;}";    \
content += ".tg .tg-996f{background-color:#C2FFD6;border-color:inherit;text-align:center;vertical-align:top}";                                                                                                                            \
content += ".tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}";                                                                                                                                                     \
content += ".tg .tg-nref{background-color:#C2FFD6;border-color:inherit;text-align:center;vertical-align:middle}";                                                                                                                         \
content += "@media screen and (max-width: 767px) {.tg {width: auto !important;}.tg col {width: auto !important;}.tg-wrap {overflow-x: auto;-webkit-overflow-scrolling: touch;margin: auto 0px;}}";                                        \
content += "body {";                          \
content +=     "font-size: 250%;";            \
content +=     "background-color:#5f9ea0";    \
content += "}";                               \
content += "form {";  \
content +=     "display: grid;";              \
content +=     "place-items: center;";        \
content +=     "}";                           \
content += ".Button {";                                                           \
content += "box-shadow: 0px 10px 14px -7px #3e7327;";                             \
content += "background:linear-gradient(to bottom, #77b55a 5%, #72b352 100%);";    \
content += "background-color:#77b55a;";                                           \
content += "border-radius:10px;";                                                 \
content += "border:2px solid #4b8f29;";                                           \
content += "display:inline-block;";                                               \
content += "cursor:pointer;";                                                     \
content += "color:#ffffff;";                                                \
content += "font-family:Arial;";                                                  \
content += "font-size:100%;";                                                     \
content += "font-weight:bold;";                                                   \
content += "padding:6px 12px;";                                                   \
content += "text-decoration:none;";                                               \
content += "text-shadow:0px 1px 0px #5b8a3c;";                                    \
content += "}";                                                                   \
content += ".Button:hover {";                                                     \
content += "background:linear-gradient(to bottom, #72b352 5%, #77b55a 100%);";    \
content += "background-color:#72b352;";                                           \
content += "}";                                                                   \
content += ".Button:active {";    \
content += "position:relative;";  \
content += "top:1px;";            \
content += "}";

#define HTML_Header()                                                                                    \
content += "<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>"; \
content += "<head>";                                                                                     \
content +=    "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'></meta>";             \
content +=    "<meta name='author' content='LowySoft' />";                                              \
content +=    "<meta name='copyright' content='LowySoft' />";                                           \
content +=    "<meta name='description' content='LowySoft thermostat setting paga' />";                 \
content +=    "<title>LowySoft Termostat</title>";                                                      \
content +=    "<style>";                                                                                \
              globalCSS();                                                                                \
content +=    "</style>";                                                                               \
content +=    "<script type='text/javascript'>";


#define HTML_Loaded(tID)                                                                \
content += "function loaded()";                                                                   \
content += "{";                                                                                   \
content +=    "document.getElementById('TermostatID').innerHTML = '";                             \
content +=     tID;                                                                               \
content +=  "';";

#define HTML_LoadedEnd() content += "}";


#define HTML_HeaderEnd()                    \
content +=    "</script>";                  \
content += "</head>"; 

#define HTML_Body(siteTitle)                                                                               \
content += "<body onload='loaded();'>";                                                                    \
    content += "<p><h1 style='text-align: center; line-height:50%'>LowySoft Termosztát</h1></p>";          \
    content += "<h2 style='text-align: center; line-height: 0%;'><label id='TermostatID'></label></h2>";   \
    content += "<h3 style='text-align: center; line-height:75%'>";                                         \
    content += siteTitle;                                                                                  \
    content += "</h3><br/>";

#define HTML_BodyEnd                                                               \
content += "<br/>";                                                                \
content += "<div style='position: relative;'>";                                    \
content +=      "<h6 style='position: fixed; bottom: 0; width:100%; left: 20px;'>";\
content +=      "LowySost Termostat (C) 2020 V: 0.02.0000<br/>";                   \
content +=      "LowySoft Termostat Web Meneger (C) 2020 V: 1.00.000";             \
content +=     "</h6>";                                                            \
content +=   "</div>";                                                             \
content +=   "</body>";

/////////////////////////////////////
// Root page

#define HTML_Root                                      \
content += "<form>";                                   \
content +=     "<fieldset style='text-align:center'>"; \
content +=         "<legend>&nbsp;Menü&nbsp;</legend>";\
content +=         "<br/>";                            \
content +=         "<input type='submit' class='Button' formaction='./thermal.html'   value='Hőfokok beállítása' style='font-size: 100%;'/><br/>";    \
content +=         "<input type='submit' class='Button' formaction='./settings.html'  value='Általános beállítások' style='font-size: 100%;'/><br/>"; \
content +=         "<input type='submit' class='Button' formaction='./ap_select.html' value='Hálózat beállítás' style='font-size: 100%;'/><br/>";     \
content +=         "<br/>";    \
content +=     "</fieldset>";  \
content += "</form>";

////////////////////////////////////
// AP Select

#define HTML_ApSelect_JS()   \
content += "var hatterSz;";                                                                 \
content += "var tcPass;";                                                                    \
content += "var tcSSID;";                                                                    \
\
content +=  "function setTextBoxEnables(numb) {";                                            \
\
content +=     "var ep = document.getElementsByName('APList')[numb].getAttributeNode('ePass').value;"; \
content +=     "var es = document.getElementsByName('APList')[numb].getAttributeNode('eSSID').value;";  \
\
content +=     "if (ep == 1) {";                                                   \
content +=         "tcPass.disabled = false;";                                              \
content +=         "tcPass.style.backgroundColor = hatterSz;";                              \
content +=     "}";                                                                         \
content +=     "else {";                                                                    \
content +=         "tcPass.disabled = true;";                                               \
content +=         "tcPass.style.backgroundColor = '#606060';";                             \
content +=     "}";                                                                         \
\
content +=     "if (es == 1) {";                                                    \
content +=         "tcSSID.disabled = false;";                                              \
content +=         "tcSSID.style.backgroundColor = hatterSz;";                              \
content +=     "}";                                                                         \
content +=     "else {";                                                                    \
content +=         "tcSSID.disabled = true;";                                               \
content +=         "tcSSID.style.backgroundColor = '#606060';";                             \
content +=     "}";                                                                         \
\
content +=     "return;";                                                                   \
content +=  "}";

#define HTML_ApSelect_SelectAp_JS()                                                     \
content +=  "function selectAP(num) {";                                                 \
content +=      "document.getElementsByName('APList')[num].checked = true;";            \
content +=      "setTextBoxEnables(num);";                                              \
content +=  "}";

#define HTML_ApSelect_Loaded(selAP)  \
content += "hatterSz = document.getElementById('Passworld').style.backgroundColor;";  \
content += "tcPass = document.getElementById('Passworld');";                          \
content += "tcSSID = document.getElementById('SSID');";                               \
\
content += "selectAP(";                                                               \
content += String(selAP);                                                             \
content += ");";                                                                      \
content += "tcPass.style.fontSize = '80%';";                                          \
content += "tcSSID.style.fontSize = '80%';";

#define HTML_ApSelectStart()                                         \
content += "<form action='ap_save_selectAP'>";                       \
content +=  "<fieldset>";                                            \
content +=      "<legend>&nbsp;Válasszon hálózatot&nbsp;</legend>";

#define HTML_ApSelectEnd()  \
content +=        "<table>";                                                                                        \
content +=            "<tr>";                                                                                       \
content +=                "<td style='text-align: right;'>SSID:</td>";                                              \
content +=                "<td><input type='text' name='SSID' id='SSID' size='32'/></td>";                          \
content +=            "</tr>";                                                                                      \
content +=            "<tr>";                                                                                       \
content +=                "<td style='text-align: right;'>Jelszó:</td>";                                            \
content +=                "<td><input type='text' name='Passworld' id='Passworld' size='64'><br/></td>";            \
content +=            "</tr>";                                                                                      \
content +=        "</table>";                                                                                       \
content +=    "</fieldset>";                                                                                        \
content +=    "<p><input type='button' class='Button' onClick='document.location.href=\"/\";' value='Vissza'/>";    \
content +=    "<input type='submit' class='Button' value='Mentés' /></p>";                                          \
content +="</form>";                                                                                         

#endif