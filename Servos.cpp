/*----------------------------------------------------------------------------------------
Essa biblioteca depende da biblioteca ESP32-Arduino-Servo-Library, criei essa biblioteca 
para deixar o arquivo principal(.ino) mais limpo.
-----------------------------------------------------------------------------------------*/

#include "Servos.h"

int servo_Delay = 20; //MG995 -> 20ms

Servo eixo1;
Servo eixo2;
Servo eixo3;

Servos::Servos(uint8_t eixo1Pin, uint8_t eixo2Pin, uint8_t eixo3Pin)
{
    _eixo1Pin = eixo1Pin;
    _eixo2Pin = eixo2Pin;
    _eixo3Pin = eixo3Pin;
}

void Servos::inicializacao()
{
    eixo1.setPeriodHertz(50); //MG995 -> 50Hz
    eixo2.setPeriodHertz(50);
    eixo3.setPeriodHertz(50);

    eixo1.attach(_eixo1Pin, 500, 2000); //MG995
    eixo2.attach(_eixo2Pin, 600, 2400); //MG90S
    eixo3.attach(_eixo3Pin, 500, 2500);
}

void Servos::sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3)
{
    eixo1.write(leituraEixo1);
    eixo2.write(leituraEixo2);
    eixo3.write(leituraEixo3);
    delay(servo_Delay);
}

void Servos::sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3, uint32_t servo_TempoEspera)
{
    eixo1.write(leituraEixo1);
    eixo2.write(leituraEixo2);
    eixo3.write(leituraEixo3);
    delay(servo_TempoEspera);
}

void Servos::checkControlType(uint8_t controlType)
{
    controlType1 = controlType;
}