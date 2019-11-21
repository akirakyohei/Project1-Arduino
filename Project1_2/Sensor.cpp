#include"Sensor.h"
#include"Arduino.h"
#include <stdio.h>

void Sensor::init(uint8_t oPin,uint8_t hPin,uint8_t tPin){
  op_pin=oPin;
  hum_pin=hPin;
  tem_pin=tPin;
  pinMode(oPin,INPUT);
  pinMode(hPin,INPUT);
  pinMode(tPin,INPUT);
}
float Sensor::getTemperatureValue(){
  pinMode(tem_pin,INPUT);
  int reading_tem=analogRead(tem_pin);
  return  reading_tem*500.0/1024.0;
}
float Sensor::getHumidityValue(){
  pinMode(hum_pin,INPUT);
  int reading_hum=analogRead(hum_pin);
  return  map(reading_hum,0,1023,0,100);
}
float Sensor::getOpticalValue(){
  pinMode(op_pin,INPUT);
  return  digitalRead(op_pin);
}
