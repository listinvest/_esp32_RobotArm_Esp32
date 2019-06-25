#include "WiFiAP.h"

int valorSensor = 0;

AsyncWebServer server80(80); //Comandos(Verificar WiFi e Enviar valor de Sensores pro aplicativo C#)
AsyncWebServer server18(18); //Controle Unitario e Programavel por parametros GET

IPAddress staticIP(10, 10, 10, 10);
IPAddress gateway(10, 10, 10, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiAP::WiFiAP(char *ssid, char *password)
{
    _ssid = ssid;
    _password = password;
}

void WiFiAP::wifiStart()
{
    WiFi.softAP(_ssid, _password);
    WiFi.softAPConfig(staticIP, gateway, subnet);

    /********* SERVIDOR 80 ************************************************************************************************************************************/
    //Receba dados do ESP32 no body do HTTP chamando a route "/sensor" pelo metodo GET
    server80.on("/sensor", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(valorSensor)); //application/json -> POST e text/plain -> GET
    });

    server80.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) { //Envia "OK" e recebe "200"
        int paramsNr = request->params();
        for (int i = 0; i < paramsNr; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            if (p->name() == "param")
            {
                conexaoAplicativoOK = p->value().toInt(); //recebendo "200"
            }
        }
        request->send(200); //enviando "OK"
    });

    server80.on("/readytosend/", HTTP_GET, [&](AsyncWebServerRequest *request) { //recebe "200"
        int paramsNr = request->params();
        for (int i = 0; i < paramsNr; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            if (p->name() == "param")
            {
                readyToSend = p->value().toInt(); //recebendo "200"
            }
        }
        request->send(200); //enviando "OK", mas não é lido pelo app C#
    });

    //Quando não encontra retorna erro pela porta 80
    server80.onNotFound([&](AsyncWebServerRequest *request) {
        request->send(404);
    });
    /***********************************************************************************************************************************************************/

    /********* SERVIDOR 18 *************************************************************************************************************************************/
    //Para enviar parametros por GET, exemplo: HTTP://IP:18/?param1=10&paramx=hello
    server18.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
        int paramsNr = request->params(); //numero de parametros recebidos
        for (int i = 0; i < paramsNr; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            //Serial.println(p->value());
            if (p->name() == "param1")
            {
                valorEixo1AP = p->value().toInt();
            }
            else if (p->name() == "param2")
            {
                valorEixo2AP = p->value().toInt();
            }
            else if (p->name() == "param3")
            {
                valorEixo3AP = p->value().toInt();
            }
            else if (p->name() == "param4")
            {
                laserStateAP = p->value().toInt();
            }
        }
        request->send(200);
    });

    server18.onNotFound([&](AsyncWebServerRequest *request) {
        request->send(404);
    });

    /************************************************************************************************************************************************************/

    server80.begin();
    server18.begin();
}

    /*
    void WiFiAP::wifiReadOn18(uint16_t *leiturasWiFiAP18)
    {
        uint16_t read[qutItemFromWiFi] = {valorEixo1AP, valorEixo2AP, valorEixo3AP, laserStateAP};
        for (int i = 0; i < qutItemFromWiFi; i++)
        {
            //talvez essa parte deixe lento
            if (readyToSend == 200 && conexaoAplicativoOK == 200) //200, codigo recebido pelo app
            {
                leiturasWiFiAP18[i] = read[i]; //leituras[i] === *(leituras + i)
            }
        }
        if (readyToSend != 200)
        {
            leiturasWiFiAP18[0] = 90;
            leiturasWiFiAP18[1] = 90;
            leiturasWiFiAP18[2] = 90;
            leiturasWiFiAP18[0] = 0; //laser OFF
        }
    }
    */

    //Função para testar com o Python e para testar a velocidade no C#
    void WiFiAP::wifiReadOn18(uint16_t *leiturasWiFiAP18)
    {
        uint16_t read[qutItemFromWiFi] = {valorEixo1AP, valorEixo2AP, valorEixo3AP, laserStateAP};
        for (int i = 0; i < qutItemFromWiFi; i++)
        {
            leiturasWiFiAP18[i] = read[i];
        }
    }


void WiFiAP::wifiStop()
{
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
}