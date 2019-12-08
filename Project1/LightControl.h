#ifndef LightControl_h
#define LightControl_h
#include <stdio.h>
#include <inttypes.h>

#define DARK_LIGHT 40

class LightControl{
private:
uint8_t pin;
uint8_t state;

public:
LightControl(uint8_t pin);
void checkUp(float opticalValue);

};

#endif
