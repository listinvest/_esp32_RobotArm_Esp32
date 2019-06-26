/*----------------------------------------------------------------------------------------
Aqui esta organizado as funcoes do laser.
-----------------------------------------------------------------------------------------*/

#include "Laser.h"

Laser::Laser(uint8_t laserPin)
{
    _laserPin = laserPin;
}

int Laser::onOff(uint8_t isLaserON, uint8_t nChances)
{
    if(isLaserON==1 && nChances>0)
    {
        digitalWrite(_laserPin,1);
        delay(350);
        return 1;
    }
    else
        digitalWrite(_laserPin,0);
    return 0;
}