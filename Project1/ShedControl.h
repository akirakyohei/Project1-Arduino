#ifndef ShedControl_h
#define ShedControl_h
#include <stdio.h>
#include <inttypes.h>
#include "Stepper.h"

#define NUMOFTIME 16
#define STEPPERREVOLUTION 128
#define SPEED 5

class ShedControl{
private:
  uint8_t pin1;
  uint8_t pin2;
  uint8_t pin3;
  uint8_t pin4;
  uint8_t maxTem;
  unsigned int numOfRounds;
  Stepper *stepper;
  int8_t state;
  uint8_t currentStep;
  unsigned int currentRound;
public:
  ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4,unsigned int numOfRound,uint8_t maxTem);
  ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4,unsigned int numOfRound);
  ShedControl(uint8_t pin1,uint8_t pin2,uint8_t pin3,uint8_t pin4);
  void init();
  void checkUp(float temperatureValue);
  void disable();
  void enable(int mode);
};
#endif
