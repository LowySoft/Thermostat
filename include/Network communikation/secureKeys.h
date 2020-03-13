/************************************************
 * 
 * LowySoft MyHome system
 * 
 * Author: Lowy
 * 
 * RSA biztonsági kulcs, a SSL kommunikációhoz.
 * Generálj magadnak sajátot, PL. az ingyenes
 * PuTTYgen programmal.
 * 
 ***********************************************/

#ifndef _RSA_SSL_Secure_Keys_
#define _RSA_SSL_Secure_Keys_

#include <Arduino.h>

static const char serverCert[] PROGMEM = R"EOF(
 - - -BEGIN CERTIFICATE - - -
 - - -END CERTIFICATE - - -
)EOF";

static const char serverKey[] PROGMEM = R"EOF(
 - - -BEGIN RSA PRIVATE KEY - - -
 - - -END RSA PRIVATE KEY - - -
)EOF";

#endif