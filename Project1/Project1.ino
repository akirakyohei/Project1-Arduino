#include "LCD.h"
#include "ShedControl.h"
#include "LightControl.h"
#include "Sensor.h"
#include "PumpControl.h"
#include <String.h>



#define soi_pin A0
#define opt_pin A1
#define tem_pin A2

#define INTERVAL_SENSOR_OFF 4
#define INTERVAL_LIGHT_ON 30
#define INTERVAL_LIGHT_OFF 400
#define INTERVAL_PUMP_ON 30
#define INTERVAL_PUMP_OFF 20
#define INTERVAL_SHED_ON 5
#define INTERVAL_SHED_OFF 400

float opticalValue ;
float temperatureValue ;
float soilMoistValue ;

long currentTime;
long preTimeSensor; 
long preTimeShed;
long preTimePump;
long preTimeLight;

LCD lcd(8,7,6,5,4,3,0,0,0);
LightControl light(2);
ShedControl shed(9,10,11,12,10);
PumpControl pump(13);
Sensor sensor(opt_pin,soi_pin,tem_pin);

void readSensor(){
  opticalValue=sensor.getOpticalValue();
  soilMoistValue=sensor.getSoilMoistValue();
  temperatureValue=sensor.getTemperatureValue();   
  lcd.update(temperatureValue,soilMoistValue,opticalValue);
  lcd.show();
}

void setInit(){
 readSensor();
 preTimeSensor=0;
 preTimeShed=0;
 preTimePump=0;
 preTimeLight=0;
};

void multiTask(){
//task sensor
if(currentTime-preTimeSensor>=INTERVAL_SENSOR_OFF){
  readSensor();
  preTimeSensor=millis();
}
//task light
if(currentTime-preTimeLight>=INTERVAL_LIGHT_OFF){
 light.checkUp(opticalValue);
  preTimeLight=millis();
}
//task pump
if(currentTime-preTimePump>=INTERVAL_PUMP_OFF){
  preTimePump=currentTime;
  while(currentTime-preTimePump<=INTERVAL_PUMP_ON){
    pump.checkUp(soilMoistValue,opticalValue);
    currentTime=millis();
  }
  preTimePump=millis();
}
//task shed
if(currentTime-preTimeShed>=INTERVAL_SHED_OFF){
  preTimeShed=currentTime;
  while(currentTime-preTimeShed<=INTERVAL_SHED_ON){
   shed.checkUp(temperatureValue);
   currentTime=millis();
  }
  preTimeShed=millis();
}
}

void setup(){
  Serial.begin(9600);
  while(!Serial);
  setInit();
  };
void loop(){
 currentTime=millis();
 Serial.print("op: ");
 Serial.println(opticalValue);
 Serial.print("tem: ");
 Serial.println(temperatureValue);
 Serial.print("soi: ");
 Serial.println(soilMoistValue);
 multiTask(); 
  };
