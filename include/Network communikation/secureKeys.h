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
-----BEGIN CERTIFICATE-----
MIICyTCCAjKgAwIBAgIUNTdaCEcOPhOX/j2gJzDxJtYkO6MwDQYJKoZIhvcNAQEL
BQAwZzELMAkGA1UEBhMCSFUxCjAIBgNVBAgMAS4xDDAKBgNVBAcMA0JhajERMA8G
A1UECgwITG93eVNvZnQxEDAOBgNVBAsMB015IEhvbWUxGTAXBgNVBAMMEHRoZXJt
b3N0YXQubG9jYWwwIBcNMjAwMzMwMTIzNTQzWhgPMjEyMDAzMDYxMjM1NDNaMGcx
CzAJBgNVBAYTAkhVMQowCAYDVQQIDAEuMQwwCgYDVQQHDANCYWoxETAPBgNVBAoM
CExvd3lTb2Z0MRAwDgYDVQQLDAdNeSBIb21lMRkwFwYDVQQDDBB0aGVybW9zdGF0
LmxvY2FsMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDCpuU+onSJNOJ5A6nb
7Pt+eQSqWLBm96G5bZrJMKvZlJq7nIpk7ZM/eDsyVgGRGTG2ymKuq+87/FUuRdkr
iP6JUmdfHvEa7dd9qu61zuv3exqq/Vrp7+20mqkepDqmbDc5HJJgF/14tWdJRmv2
Rn019uTWs5oMKdBZyHsU86v1kQIDAQABo3AwbjAdBgNVHQ4EFgQUUqP3azJVpC53
nYLcVAdBirrzmqMwHwYDVR0jBBgwFoAUUqP3azJVpC53nYLcVAdBirrzmqMwDwYD
VR0TAQH/BAUwAwEB/zAbBgNVHREEFDASghB0aGVybW9zdGF0LmxvY2FsMA0GCSqG
SIb3DQEBCwUAA4GBACTb4xxi3Ca6Ag8gTW36cKDiY8Zxyc+V7ar7Zr9OdTZ7aT95
qRyYtDvJx1PUKUaxAyvMODYz+smaVS8RfNlCQ62rdryk6s8aEVuDuTurFohF1gMJ
SDT22Jxz81/NZEshWTW2uNbweIYqJxzS1qdn6ADskw7jgM+wEM6ttVqyPe4Q
-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM = R"EOF(
-----BEGIN PRIVATE KEY-----
MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAMKm5T6idIk04nkD
qdvs+355BKpYsGb3obltmskwq9mUmrucimTtkz94OzJWAZEZMbbKYq6r7zv8VS5F
2SuI/olSZ18e8Rrt132q7rXO6/d7Gqr9Wunv7bSaqR6kOqZsNzkckmAX/Xi1Z0lG
a/ZGfTX25Nazmgwp0FnIexTzq/WRAgMBAAECgYEAtggtym1SXh2+zTzH1IvChXvX
CRb3oNNjwmzlm9CQZWG7ckfqhIhIc8qUUXZs8KyG+VI7Bu5zQ72uSx+3ACeVIGJW
BlnTdjVecbuqr2Hh8kFfMtdtbO13kz4pBgODWcdUToaRuNYGz3Cp6z5TVjbJNjRK
UW2ckdmgKGnTujM8iSECQQD6TS8rnEuDhmopblqcZFbDcCkBAZDPDSwdzunPe6yz
Qx/GjBuwLjorbRRntJcZkf9XKoXGk9SkgeNQzFHK7g+TAkEAxxVfXlJe5nAOfBHN
qVn/Z4/S/esfvbaGueK1w7K5Hj7TfA0FDMCeYNYq8cT0AGCu5ghrOX0L4xA70GsT
/y10ywJBAMnGNNNkIF+7mJMjmbnfDS5pmTRtba3rwXeaGFOhMDwmTVRCGAPzkAL3
4O4k33XGgt9isQq+mzmuV3AH9ZuwQy8CQEcOMsa4gZSfxBu2QwBB1e3BoJ3uMJsG
rZlk+FkLzhSkedkZ0IaXrS+E4Tj/gdMsrt/9ez++iOKXJbIitbVrJPcCQHlyBnT+
JEI3Q+DxV65TOgO6Jqg/brx2E7qFZqz9Dxm1TQxODfV6L5XDEwtiu4x7aA4jIHcN
SXaVVqH09ZTZiU8=
-----END PRIVATE KEY-----
)EOF";

#endif