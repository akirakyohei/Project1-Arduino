#ifndef Sensor_h
#define Sensor_h
#include <inttypes.h>



class Sensor{
 private:
 uint8_t tem_pin;
 uint8_t soi_pin;
uint8_t op_pin;
  public:
    Sensor(uint8_t oPin,uint8_t sPin,uint8_t tPin);
    float getTemperatureValue();
    float getSoilMoistValue();
    float getOpticalValue();
    int getAVG(uint8_t pin);
};

#endif
