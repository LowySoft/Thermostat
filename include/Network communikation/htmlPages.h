#ifndef _html_Pages_h
#define _html_Pages_h

#include <Arduino.h>
#include "Network communikation/htmlPageElements.h"

namespace htmlPages {

    void createRoot();  // Főoldal létregozása
    void createAPSelect();  // Hállózatválasztó lap
    void saveAPSelect();    // Hállózat hitelesítési adatainak mentése
}

#endif