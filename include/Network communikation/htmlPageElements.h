#ifndef HTML_Page_Elements_H
#define HTML_Page_Elements_H

#include <Arduino.h>

namespace htmlPageElements {

    /////////////////////////////////////
    // Fejléc és törzs közös elemek
    
    void globalCSS(String &content);                // A HTML lapok stílusbeállításai

    void HTML_Header(String &content);              // HTML lap fejléc eleje
    void HTML_Loaded(String tID, String &content);  // Betőltéskór lefutó JS kód eleje
    void HTML_LoadedEnd(String &content);           // Betőltéskór lefutó JS kód vége
    void HTML_HeaderEnd(String &content);           // HTML lap fejléc vége

    void HTML_Body(String siteTitle, String &content);  // HTML lap törzsének nyitása
    void HTML_BodyEnd(String &content);                 // HTML lap törzsének zárása


    /////////////////////////////////////
    // Root page

    void HTML_Root(String &content);                    // kezdőlap tőrzse

    ////////////////////////////////////
    // AP Select (Hállózatválasztás)

    void HTML_ApSelect_JS(String &content);                     // SSID és Jelszó textboxok engedélyezése/tiltása
    void HTML_ApSelect_SelectAp_JS(String &content);            // Hállózatkiválasztó JavaScript
    void HTML_ApSelect_Loaded(uint8_t selAP, String &content);  // A lap megnyitásakor kiválasztja az aktuális AP-t. (Loaded_JS-be.)
    void HTML_ApSelectStart(String &content);                   // Laptörzs kezdete
    void HTML_ApSelectEnd(String &content);                     // Laptőrzs vége

}

#endif