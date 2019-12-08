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
		digitalWrite(pin,HIGH);
		state=1;
	}else if(state==1){
		digitalWrite(pin,LOW);
		state=0;
	}
};
