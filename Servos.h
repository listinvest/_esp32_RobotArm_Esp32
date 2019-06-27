#ifndef Servos_h
#define Servos_h

#include "Arduino.h"
#include <ESP32Servo.h>

class Servos
{
public:
  Servos(uint8_t eixo1Pin, uint8_t eixo2Pin, uint8_t eixo3Pin);
  void inicializacao(uint8_t minEixo1, uint8_t maxEixo1, uint8_t minEixo2, uint8_t maxEixo2, uint8_t minEixo3, uint8_t maxEixo3);
  void sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3);

private:
  uint8_t _eixo1Pin;
  uint8_t _eixo2Pin;
  uint8_t _eixo3Pin;
  uint8_t _minEixo1;
  uint8_t _maxEixo1;
  uint8_t _minEixo2;
  uint8_t _maxEixo2;
  uint8_t _minEixo3;
  uint8_t _maxEixo3;
};

#endif
