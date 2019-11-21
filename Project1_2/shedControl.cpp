#include"Arduino.h"
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
//sang D0=0, toi D0=1, sang thi keo rem, toi thi mo
#include"Arduino.h"
#include"Sensor.h"
#include"Stepper.h"

class shedControl{
  private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pin3;
    uint8_t pin4;
    long max;
    long min;
    int stepsPerRevolution =4096;
     Stepper *myStepper;
  public:
    void init(uint8_t pin_1, uint8_t pin_2, uint8_t pin_3, uint8_t pin_4){
      pin1=pin_1;
      pin2=pin_2;
      pin3=pin_3;
      pin4=pin_4;
      
      myStepper =new Stepper(stepsPerRevolution,pin1,pin2,pin3,pin4);
      myStepper->setSpeed(60);
    }
    void Shed(float opticalValue){
      if(opticalValue>max){
        myStepper->step(stepsPerRevolution);
      }
      else if(opticalValue<min)
        myStepper->step(-stepsPerRevolution);    
    };
};
