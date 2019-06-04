/*----------------------------------------------------------------------------------------
Aqui esta organizado as funcoes do laser.
-----------------------------------------------------------------------------------------*/

#include "Laser.h"

Laser::Laser(uint8_t laserPin)
{
    _laserPin = laserPin;
}

void Laser::onOff(bool isLaserON)
{
    if(isLaserON)
        digitalWrite(_laserPin,1);
    else
        digitalWrite(_laserPin,0);
}
