#ifndef PumpControl_h
#define PumpControl_h

#include <stdio.h>
#include <inttypes.h>

#define NUMOFTIME 200
#define DARK_LIGHT 40
class PumpControl{
private:
  uint8_t pin;
  uint8_t maxSoil;
  uint8_t minSoil;
  uint8_t speed;
  uint8_t state;

public:
  PumpControl(uint8_t pin,uint8_t maxSoil,uint8_t minSoil,uint8_t speed);
  PumpControl(uint8_t pin,uint8_t maxSoil,uint8_t minSoil);
   PumpControl(uint8_t pin,uint8_t speed);
  PumpControl(uint8_t pin);
  void init();
  void setSpeed(uint8_t s);
  void enable();
  void disable();
  void checkUp(float soilMoistValue,float opticalValue);
  void setMaxSoil(uint8_t maxValue);
  void setMinSoil(uint8_t minValue);
};
#endif
