/********************************************************************************************
 * Observações: 1) O loop() é uma task realizada no core 1 com prioridade 1.
 *              2) Sempre coloque um delay(1000); nas tasks não utilizadas.
 * 
 * ******************************************************************************************/

//----------------------------BIBLIOTECAS----------------------------
#include "Servos.h"
#include "Potenciometro.h"
#include "WifiAP.h"
//-------------------------------------------------------------------

//----------------------------DEFINES--------------------------------
#define buttonControlType 4
//-------------------------------------------------------------------

//---------------------------CONSTRUTORES----------------------------
TaskHandle_t Task1, Task2;
Servos servos(13, 12, 14);                //Pinos dos servos ->recomendados 2,4,12-19,21-23,25-27,32-33
Potenciometro pot(32, 35, 34, 39);        // APENAS ADC1
WiFiAP wifiAP("robotarm", "0xcrossbots"); // SSID e PW do AP a ser criado
//-------------------------------------------------------------------

//----------------------------VARIAVEIS------------------------------
bool wifiOn = false;
const int numeroDeControles = 3;
uint8_t controlType = 0;

/*Variaveis para o Timer da Troca de Controles*/
int ultimoEstado = 0;
int ultimoValor = 0;
const int TimerDelay = 50;
unsigned long Timer = 0;
/**/

uint16_t *leiturasPotenciometro;
uint16_t *leiturasWiFiAP18;
//-------------------------------------------------------------------

void setup()
{
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 0, &Task1, 0);
  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 0, &Task2, 1);
  Serial.begin(115200);
  servos.inicializacao();
  leiturasPotenciometro = (uint16_t *)malloc(5 * sizeof(uint16_t));
  leiturasWiFiAP18 = (uint16_t *)malloc(6 * sizeof(uint16_t));
}

void Task1code(void *parameter)
{
  for (;;)
  {
    int valor = digitalRead(buttonControlType);
    if (valor != ultimoValor)
    {
      Timer = millis();
    }
    if ((millis() - Timer) > TimerDelay)
    {
      if (valor != ultimoEstado)
      {
        if (valor == 1)
        {
          if (controlType < (numeroDeControles - 1))
          {
            controlType = controlType + 1;
          }
          else
          {
            controlType = 0;
          }
        }
      }
      ultimoEstado = valor;
    }
    ultimoValor = valor;
    servos.checkControlType(controlType);
  }
}

void Task2code(void *parameter)
{
  for (;;)
  {
    if (controlType == 0)  //Aguardando
    {
      if (wifiOn == true)
      {
        wifiAP.wifiStop();
        wifiOn = false;
      }
    }
    else if (controlType == 1) //Potenciometro
    {
      pot.potRead(leiturasPotenciometro);
      servos.sendMoves(leiturasPotenciometro[0], leiturasPotenciometro[1], leiturasPotenciometro[2]);
    }
    else if (controlType == 2) //WiFiAP
    {
      if (wifiOn == false)
      {
        wifiAP.wifiStart();
        wifiOn = true;
        pot.potRead(leiturasPotenciometro);
      }
      wifiAP.wifiReadOn18(leiturasWiFiAP18, leiturasPotenciometro[0], leiturasPotenciometro[1], leiturasPotenciometro[2]);
      servos.sendMoves(leiturasWiFiAP18[0], leiturasWiFiAP18[1], leiturasWiFiAP18[2]);
    }
    else
    {
      if (wifiOn == true)
      {
        wifiAP.wifiStop();
        wifiOn = false;
      }
    }
  }
}

void loop()
{
  delay(1000);
}
