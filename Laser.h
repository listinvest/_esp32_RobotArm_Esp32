#ifndef Laser_h
#define Laser_h

#include "Arduino.h"

class Laser
{
public:
  Laser(uint8_t laserPin);
  void onOff(uint8_t isLaserON);

private:
  uint8_t _laserPin;
};

#endif
