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

void Servos::inicializacao()
{
    eixo1.setPeriodHertz(50);//50Hz -> padrao
    eixo2.setPeriodHertz(50);
    eixo3.setPeriodHertz(50);

    eixo1.attach(_eixo1Pin, 600, 2400);//MG90S
    eixo2.attach(_eixo2Pin, 600, 2400); 
    eixo3.attach(_eixo3Pin, 600, 2400);
}

void Servos::sendMoves(uint16_t leituraEixo1, uint16_t leituraEixo2, uint16_t leituraEixo3)
{
    eixo1.write(leituraEixo1);
    eixo2.write(leituraEixo2);
    eixo3.write(leituraEixo3);
    delay(servo_Delay);
}