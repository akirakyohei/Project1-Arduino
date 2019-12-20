#include"Sensor.h"
#include"Arduino.h"
#include <stdio.h>

float Sensor::getTemperatureValue(uint8_t tem_pin){
  int reading_tem=getAVG(tem_pin);
  return  reading_tem*500.0/1024.0;
}
float Sensor::getSoilMoistValue(uint8_t soi_pin){
  int reading_soi=getAVG(soi_pin);
  return  map(reading_soi,0,1023,0,100);
}
float Sensor::getOpticalValue(uint8_t op_pin){
   int reading_opt=getAVG(op_pin);
  return   map(reading_opt,0,1023,0,100);
}
int Sensor::getAVG(uint8_t pin){
  int value =0;
  for(int i=0;i<10;i++){
    value+=analogRead(pin);
    delay(10);
  }
   return value/10;
}
