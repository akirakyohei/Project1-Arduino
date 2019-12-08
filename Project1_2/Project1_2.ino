#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "LCD.h"
#include "ShedControl.h"
#include "LightControl.h"
#include "Sensor.h"
#include "PumpControl.h"
#include <String.h>
SemaphoreHandle_t xSerialSemaphore;

#define pumpPin 2
#define lightPin 9
#define hPin A0
#define oPin A1
#define tPin A2
float o=0;
float h=0;
float t=0;



LCD lcd(8,7,6,5,4,3,"0","0","0") ;
ShedControl shed;
PumpControl pump;
Sensor sensor;
lightControl light;



void TaskLcd( void *pvParameters );
void TaskShed( void *pvParameters );
void TaskPump(void *pvParameters );
void TaskLight(void *pvParameters );

void setInit( void){
  light.init(lightPin);
  pump.init(pumpPin);
  sensor.init(oPin,hPin,tPin);
  shed.init(2,3,4,5);
  
  
  };
// the setup function runs once when you press reset or power the board
void setup() {
  
 setInit();
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

if(xSerialSemaphore==NULL){
  xSerialSemaphore=xSemaphoreCreateMutex();
  if((xSerialSemaphore)!=NULL){
    xSemaphoreGive((xSerialSemaphore));
  }
}
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskLcd
    ,  (const portCHAR *)"Lcd"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskShed
    ,  (const portCHAR *) "Shed"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );
    xTaskCreate(TaskPump
    , (const portCHAR *) "Pump"
    ,128
    ,NULL
    ,1
    ,NULL);
    xTaskCreate(
      TaskLight
      ,(const portCHAR *) "Light"
      ,128
      ,NULL
      ,1
      ,NULL);

}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskLcd(void *pvParameters)  // This is a task.
{
  (void) pvParameters;



  for (;;) // A Task shall never return or exit.
  {
    //do


    lcd.show();
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t)6)==pdTRUE){
      xSemaphoreGive(xSerialSemaphore);
    }
  vTaskDelay(1);
  }
}
void TaskLight(void *pvParameters){
  (void)pvParameters;
  for(;;)
  { 
    //do
o=sensor.getOpticalValue();
t=sensor.getTemperatureValue();
    light.Light(o,t);
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t)6)==pdTRUE){
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1);
    }
}
void TaskShed(void *pvParameters){
  (void)pvParameters;
  for(;;)
  {//do
 o=sensor.getOpticalValue();
shed.Shed(o);
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 6)==pdTRUE){
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1);
    }
}
void TaskPump(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
 for(;;)
  {
    //do
    h=sensor.getHumidityValue();
    pump.doPump(h);
     if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1);
    }
}
