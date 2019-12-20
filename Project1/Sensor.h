
#ifndef Sensor_h
#define Sensor_h
#include"Arduino.h"


class Sensor{
  public:
 
    float getTemperatureValue(uint8_t tem_pin);
    float getSoilMoistValue(uint8_t soi_pin);
    float getOpticalValue(uint8_t op_pin);
   int  getAVG(uint8_t pin);
};

#endif
