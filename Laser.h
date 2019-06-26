#ifndef Laser_h
#define Laser_h

#include "Arduino.h"

class Laser
{
public:
  Laser(uint8_t laserPin);
  int onOff(uint8_t isLaserON, uint8_t nChances);

private:
  uint8_t _laserPin;
};

#endif
