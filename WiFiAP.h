#ifndef WiFiAP_h
#define WiFiAP_h

#define qutItemFromWiFi 4 //3 eixos + laser

#include "Arduino.h"
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class WiFiAP
{
public:
  WiFiAP(char *ssid, char *password);
  void wifiStart();
  void wifiReadOn18(uint16_t *leiturasWiFiAP18, uint16_t pot1, uint16_t pot2, uint16_t pot3);
  void wifiStop();

private:
  char *_ssid;
  char *_password;
  uint8_t conexaoAplicativoOK;
  uint8_t readyToSend;
  uint16_t valorEixo1AP;
  uint16_t valorEixo2AP;
  uint16_t valorEixo3AP;
  uint16_t laserStateAP;
};

#endif
