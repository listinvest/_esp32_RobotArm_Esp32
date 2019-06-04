#ifndef Servos_h
#define Servos_h

#include "Arduino.h"
#include <ESP32Servo.h>

class Servos
{
public:
  Servos(uint8_t eixo1Pin, uint8_t eixo2Pin, uint8_t eixo3Pin);
  void inicializacao();
  void sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3);
  void sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3, uint32_t servo_TempoEspera);
  void checkControlType(uint8_t controlType);

private:
  uint8_t _eixo1Pin;
  uint8_t _eixo2Pin;
  uint8_t _eixo3Pin;
  uint8_t controlType1;
};

#endif
