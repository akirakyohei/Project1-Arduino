#include"Sensor.h"
#include"Arduino.h"
#include <stdio.h>

Sensor::Sensor(uint8_t oPin,uint8_t sPin,uint8_t tPin){
   op_pin=oPin;
  soi_pin=sPin;
  tem_pin=tPin;
  pinMode(oPin,INPUT);
  pinMode(sPin,INPUT);
  pinMode(tPin,INPUT);
}


float Sensor::getTemperatureValue(){
 int temperatureValue=getAVG(tem_pin);
  return  temperatureValue*500.0/1024;
}


float Sensor::getSoilMoistValue(){
int soilMoistValue=getAVG(soi_pin);
return 100-(soilMoistValue*1.0/1023)*100;
}


float Sensor::getOpticalValue(){
int opticalValue=getAVG(op_pin);
return 100-map(opticalValue,1024,0,0,100);
}

int Sensor::getAVG(uint8_t pin){
  int value =0;
  for(int i=0;i<10;i++){
    value+=analogRead(pin);
    delay(10);
  }
   return value/10;
}
