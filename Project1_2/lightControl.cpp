
#include"Arduino.h"
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

class lightControl{
	
	private: 
	uint8_t light_pin;
	float tmax=30;
	float tmin=20;
	float lmin=10;
	float lmax=20;

	public:
	void init(uint8_t light){
			light_pin = light;
			pinMode(light_pin,OUTPUT);
		};
		void Light(float opticalValue, float temperatureValue){
			if(opticalValue> lmax or temperatureValue> tmax)
			digitalWrite(light_pin,LOW);
			else if(opticalValue<lmin or temperatureValue< lmin)
			digitalWrite(light_pin,HIGH);
		};
	};
