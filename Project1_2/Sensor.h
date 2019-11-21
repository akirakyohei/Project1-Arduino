
#ifndef Sensor_h
#define Sensor_h
#include"Arduino.h"


class Sensor{
 private:
 uint8_t tem_pin;
 uint8_t hum_pin;
uint8_t op_pin;
  public:
  void init(uint8_t oPin,uint8_t hPin,uint8_t tPin);
    float getTemperatureValue();
    float getHumidityValue();
    float getOpticalValue();
};

#endif
