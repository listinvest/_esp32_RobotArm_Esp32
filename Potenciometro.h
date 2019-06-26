#ifndef Potenciometro_h
#define Potenciometro_h

#define qutItemFromPot 4 //3 eixos + laser

#include "Arduino.h"

class Potenciometro
{
public:
  Potenciometro(uint8_t potEixo1, uint8_t potEixo2, uint8_t potEixo3, uint8_t buttonLaser);
  void potRead(uint16_t *leiturasPotenciometro);
private:
  uint8_t _potEixo1;
  uint8_t _potEixo2;
  uint8_t _potEixo3;
  uint8_t _buttonLaser;
  uint16_t potEixo1Valor;
  uint16_t potEixo2Valor;
  uint16_t potEixo3Valor;
  bool buttonLaserState;
};

#endif
