#include "PumpControl.h"
#include "Arduino.h"

 PumpControl::PumpControl(uint8_t pin,uint8_t maxSoil,uint8_t minSoil,uint8_t speed){
 this->pin=pin;
 this->maxSoil=maxSoil;
 this->minSoil=minSoil;
 this->speed=speed;
 init();
 };
 
 PumpControl::PumpControl(uint8_t pin,uint8_t maxSoil,uint8_t minSoil){
   this->pin=pin;
    this->maxSoil=maxSoil;
    this->minSoil=minSoil;
    this->speed=255;
    init();
 };
  PumpControl::PumpControl(uint8_t pin,uint8_t speed ){
   this->pin=pin;
   this->maxSoil=60;
   this->minSoil=40;
   this->speed=speed;
   init();
 };
 PumpControl::PumpControl(uint8_t pin){
   this->pin=pin;
   this->maxSoil=60;
   this->minSoil=40;
   this->speed=255;
   init();
 };
 void PumpControl::init(){
   digitalWrite(pin,0);
   state=0;
   
 };
 void PumpControl::setSpeed(uint8_t s){
  if(0<=s)
   this->speed=s;
 };
  void PumpControl:: enable(){
  for(int i=0;i<NUMOFTIME;i++){
    analogWrite(pin,speed);
  }
  };
  void PumpControl::disable(){
    analogWrite(pin,0);
  };
  
 void PumpControl::checkUp(float soilMoistValue,float opticalValue){
   if(soilMoistValue < minSoil & opticalValue > DARK_LIGHT){
      Serial.print("Pump ON ");
     enable();
     state=1;
   }else if(soilMoistValue > maxSoil| opticalValue<DARK_LIGHT){
     Serial.print("Pump OFF ");
     disable();
     state=0;
   }else{
     if(state==1){
    enable();  
     }
   }
   
 };
