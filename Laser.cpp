/*----------------------------------------------------------------------------------------
Aqui esta organizado as funcoes do laser.
-----------------------------------------------------------------------------------------*/

#include "Laser.h"

Laser::Laser(uint8_t laserPin)
{
    _laserPin = laserPin;
}

void Laser::onOff(uint8_t isLaserON)
{
    if(isLaserON==1)
        digitalWrite(_laserPin,1);
    else
        digitalWrite(_laserPin,0);
}