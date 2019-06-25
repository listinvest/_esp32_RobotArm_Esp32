/********************************************************************************************
 * Observações: 1) O loop() é uma task realizada no core 1 com prioridade 1.
 *              2) Sempre coloque um delay(1000); nas tasks não utilizadas.
 * 
 * ******************************************************************************************/

//----------------------------BIBLIOTECAS----------------------------
#include "Servos.h"
#include "WifiAP.h"
#include "Laser.h"
//-------------------------------------------------------------------

//----------------------------DEFINES--------------------------------
#define buttonControlOnOff 4
//-------------------------------------------------------------------

//---------------------------CONSTRUTORES----------------------------
TaskHandle_t Task1, Task2;
Servos servos(13, 12, 14);                //Pinos dos servos ->recomendados 2,4,12-19,21-23,25-27,32-33
Laser laser(27);
WiFiAP wifiAP("robotarm", "0xcrossbots"); // SSID e PW do AP a ser criado
//-------------------------------------------------------------------

//----------------------------VARIAVEIS------------------------------
bool wifiOn = false;
uint8_t controlOnOff = 0;

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
  //Serial.begin(115200);
  servos.inicializacao();
  leiturasWiFiAP18 = (uint16_t *)malloc(qutItemFromWiFi * sizeof(uint16_t));
}

void Task1code(void *parameter)
{
  for (;;)
  {
    int valor = digitalRead(buttonControlOnOff);
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
          if (controlOnOff < 1)
          {
            controlOnOff = controlOnOff + 1;
          }
          else
          {
            controlOnOff = 0;
          }
        }
      }
      ultimoEstado = valor;
    }
    ultimoValor = valor;
  }
}

void Task2code(void *parameter)
{
  for (;;)
  {
    if (controlOnOff == 0)  //Aguardando
    {
      if (wifiOn == true)
      {
        //led OFF ou red
        wifiAP.wifiStop();
        wifiOn = false;
      }
    }
    else if (controlOnOff == 1) //WiFiAP
    {
      if (wifiOn == false)
      {
        //led ON ou green
        wifiAP.wifiStart();
        wifiOn = true;
      }
      wifiAP.wifiReadOn18(leiturasWiFiAP18);
      laser.onOff(leiturasWiFiAP18[3]);
      servos.sendMoves(leiturasWiFiAP18[0], leiturasWiFiAP18[1], leiturasWiFiAP18[2]);
    }
  }
}

void loop()
{
  delay(1000);
}
