/*----------------------------------------------------------------------------------------
Essa biblioteca depende da biblioteca ESP32-Arduino-Servo-Library e serve para controlá-la.
-----------------------------------------------------------------------------------------*/

#include "Servos.h"

int servo_Delay = 20; //min = 15ms

Servo eixo1;
Servo eixo2;
Servo eixo3;

Servos::Servos(uint8_t eixo1Pin, uint8_t eixo2Pin, uint8_t eixo3Pin)
{
    _eixo1Pin = eixo1Pin;
    _eixo2Pin = eixo2Pin;
    _eixo3Pin = eixo3Pin;
    }

void Servos::inicializacao(uint8_t minEixo1, uint8_t maxEixo1, uint8_t minEixo2, uint8_t maxEixo2, uint8_t minEixo3, uint8_t maxEixo3)
{
    _minEixo1 = minEixo1;
    _maxEixo1 = maxEixo1;
    _minEixo2 = minEixo2;
    _maxEixo2 = maxEixo2;
    _minEixo3 = minEixo3;
    _maxEixo3 = maxEixo3;

    eixo1.setPeriodHertz(50);//50Hz -> padrao
    eixo2.setPeriodHertz(50);
    eixo3.setPeriodHertz(50);

    eixo1.attach(_eixo1Pin, 600, 2400);//MG90S
    eixo2.attach(_eixo2Pin, 600, 2400); 
    eixo3.attach(_eixo3Pin, 600, 2400);
}

void Servos::sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3)
{
    if(leituraEixo1 > minEixo1 && leituraEixo1 < maxEixo1)
        eixo1.write(leituraEixo1);
    if(leituraEixo2 > minEixo2 && leituraEixo2 < maxEixo2)
        eixo2.write(leituraEixo2);
    if(leituraEixo2 > minEixo2 && leituraEixo2 < maxEixo2)
        eixo3.write(leituraEixo3);
    delay(servo_Delay);
}