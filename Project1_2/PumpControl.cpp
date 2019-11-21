#include"Sensor.h"
#include"Arduino.h"
#include<stdio.h>

class PumpControl{
	private:
		uint8_t pump_pin;
		float max_value = 80;
		float min_value = 60;
	public:
		void init(uint8_t pump){
			pump_pin = pump;
			pinMode(pump_pin,OUTPUT);
		}
		void doPump(float humidityValue){
			float Value = humidityValue;
			if(Value<min_value) digitalWrite(pump_pin,HIGH);
			else if(Value>max_value) digitalWrite(pump_pin,LOW);
	}
};
