/*-----------------------------------------------------------------------------------------------
Essa biblioteca foi criada para enviar as leituras dos potenciometros para quem quiser chama-la.
-------------------------------------------------------------------------------------------------*/

#include "Potenciometro.h"

Potenciometro::Potenciometro(uint8_t potEixo1, uint8_t potEixo2, uint8_t potEixo3, uint8_t buttonLaser)
{
  _potEixo1 = potEixo1;
  _potEixo2 = potEixo2;
  _potEixo3 = potEixo3;
  _buttonLaser = buttonLaser;
}

void Potenciometro::potRead(uint16_t *leiturasPotenciometro)
{
  potEixo1Valor = analogRead(_potEixo1); //0 ate 4095
  potEixo2Valor = analogRead(_potEixo2);
  potEixo3Valor = analogRead(_potEixo3);
  buttonLaserState = digitalRead(_buttonLaser);

  potEixo1Valor = map(potEixo1Valor, 0, 4095, 0, 180); //mudando pra 1-180
  potEixo2Valor = map(potEixo2Valor, 0, 4095, 0, 180);
  potEixo3Valor = map(potEixo3Valor, 0, 4095, 0, 180);


  uint16_t read[4] = {potEixo1Valor, potEixo2Valor, potEixo3Valor, buttonLaserState};
  for (int i = 0; i < 5; i++)
  {
    leiturasPotenciometro[i] = read[i]; //leituras[i] === *(leituras + i)
  }
}
