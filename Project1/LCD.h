#include "Arduino.h"
#include <LiquidCrystal.h>

#define TIME_MSG_LEN  11   
#define TIME_HEADER  255

class LCD
{
private:
    unsigned long time;
    float valueOfSegmentOne;
    float valueOfSegmentTwo;
    float valueOfSegmentThree;
    uint8_t d1,d2,d3,d4,rw,enable;
    LiquidCrystal *lcd;
    byte charmap[8] = {0x06,0x09,0x09,0x06,0x00,0x00,0x00,0x00};
public:
    LCD(uint8_t rw,uint8_t enable,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,float valueOfSegmentOne, float valueOfSegmentTwo, float valueOfSegmentThree);
    ~LCD();
    void update(float valueOfSegmentOne, float valueOfSegmentTwo, float valueOfSegmentThree);
    void show();
};
