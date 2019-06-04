#ifndef Laser_h
#define Laser_h

#include "Arduino.h"

class Laser
{
public:
  Laser(uint8_t laserPin);
  void onOff(bool isLaserON);

private:
  uint8_t _laserPin;
};

#endif
