#include "LightControl.h"
#include "Arduino.h"

LightControl::LightControl(uint8_t pin){
  this->pin =pin;
  pinMode(this->pin,OUTPUT);
  digitalWrite(this->pin,LOW);
  state=0;
};
void LightControl ::checkUp(float opticalValue){
  if(opticalValue < DARK_LIGHT && state ==0){
   Serial.println("Light ON");
    digitalWrite(pin,HIGH);
    state=1;
  }else if(opticalValue > DARK_LIGHT && state==1){
     Serial.print("Light OFF");
    digitalWrite(pin,LOW);
    state=0;
  }
};
