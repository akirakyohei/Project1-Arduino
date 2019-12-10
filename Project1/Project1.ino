#include "LCD.h"
#include "ShedControl.h"
#include "LightControl.h"
#include "Sensor.h"
#include "PumpControl.h"
#include <String.h>



#define soi_pin A0
#define opt_pin A1
#define tem_pin A2

#define INTERVAL_SENSOR_OFF 400
#define INTERVAL_LIGHT_OFF 400
#define INTERVAL_PUMP_OFF 400
#define INTERVAL_SHED_ON 200
#define INTERVAL_SHED_OFF 0

float opticalValue ;
float temperatureValue ;
float soilMoistValue ;

unsigned long currentTime;
unsigned long preTimeSensor; 
unsigned long preTimeShed;
unsigned long preTimePump;
unsigned long preTimeLight;

LCD lcd(8,7,6,5,4,3,0,0,0);
LightControl light(2);
ShedControl shed(9,10,11,12,3);
PumpControl pump(13,200);
Sensor sensor(opt_pin,soi_pin,tem_pin);

void readSensor(){
  opticalValue=sensor.getOpticalValue();
  soilMoistValue=sensor.getSoilMoistValue();
  temperatureValue=sensor.getTemperatureValue();   
  lcd.update(temperatureValue,soilMoistValue,opticalValue);
  lcd.show();
}

void setInit(){
 preTimeSensor=0;
 preTimeShed=0;
 preTimePump=0;
 preTimeLight=0;
};

void multiTask(){
  //reset when max memory
 if(currentTime<preTimeShed){
  setInit();
 }
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
    pump.checkUp(soilMoistValue,opticalValue);
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
  setInit();
  Serial.begin(9600);
  while(!Serial);
  readSensor();
  };
void loop(){
 currentTime=millis();
 long h=millis();
 Serial.print("op: ");
 Serial.println(opticalValue);
 Serial.print("tem: ");
 Serial.println(temperatureValue);
 Serial.print("soi: ");
 Serial.println(soilMoistValue);
 multiTask(); 
// shed.checkUp(temperatureValue);
    Serial.println(millis()-h);
  };
