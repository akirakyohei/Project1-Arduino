#include "ShedControl.h"
#include "Arduino.h"

ShedControl::ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4,unsigned int numOfRound) {
this->pin1=pin1;
this->pin2=pin2;
this->pin3=pin3;
this->pin4=pin4;
this->maxTem=20;
this->numOfRounds=numOfRound;
init();
};

ShedControl::ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4,unsigned int numOfRound,uint8_t maxTem){
this->pin1=pin1;
this->pin2=pin2;
this->pin3=pin3;
this->pin4=pin4;
this->maxTem=maxTem;
this->numOfRounds=numOfRound;
init();
  };
ShedControl::ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4) {
this->pin1=pin1;
this->pin2=pin2;
this->pin3=pin3;
this->pin4=pin4;
this->maxTem=40;
this->numOfRounds=4294967295;
init();
};

    void ShedControl::init() {
      stepper =new Stepper(4096,pin1,pin2,pin3,pin4);
      stepper->setSpeed(SPEED);
      currentStep=0;
      currentRound=0;
      state=1;
    };

    void ShedControl::disable(){
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,LOW);
      digitalWrite(pin3,LOW);
      digitalWrite(pin4,LOW);
    };
    void ShedControl::enable(int mode ){
stepper->step(mode*STEPPERREVOLUTION);
    }

    void ShedControl::checkUp(float temperatureValue){
Serial.print("state");
Serial.println(state);
if (temperatureValue > maxTem && state!=-1){
     Serial.print("Shed ON 1 ");
  enable(1);
  currentStep=currentStep+1;
  Serial.print("currentStep");
  Serial.println(currentStep);
  if(currentStep==NUMOFTIME){
    currentRound=currentRound+1;
    Serial.print("currentRound");
    Serial.println(currentRound);
    currentStep&=0x00;
  }
  if(currentRound==numOfRounds){
       Serial.print("Shed OFF ");
   disable();
    state=-1;
    currentRound&=0;
  }
 
}else if (temperatureValue < maxTem && state!=1){
   Serial.print("Shed ON -1 ");
  enable(-1);
  currentStep|=0x01;
  if(currentStep==NUMOFTIME){
    currentRound|=0x01;
    currentStep&=0x00;
  }
  if(currentRound==numOfRounds){
    Serial.print("Shed OFF ");
    disable();
    state=1;
    currentRound&=0;
  }

}else {
  disable();
}

    };
