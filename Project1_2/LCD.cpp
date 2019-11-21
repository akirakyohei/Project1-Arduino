#include "LCD.h"
#include <String.h>

LCD::LCD(uint8_t rw,uint8_t enable,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,String valueOfSegmentOne, String valueOfSegmentTwo, String valueOfSegmentThree){
    this->rw=rw;
    this->enable=enable;
    this->d1=d1;
    this->d2=d2;
    this->d3=d3;
    this->d4=d4;
    this->valueOfSegmentOne=valueOfSegmentOne;
    this->valueOfSegmentTwo=valueOfSegmentTwo;
    this->valueOfSegmentThree=valueOfSegmentThree;
    lcd=new LiquidCrystal(rw,enable,d1,d2,d3,d4);
    lcd->begin(16,2);
}
LCD::~LCD(){

}
void LCD::update(String valueOfSegmentOne, String valueOfSegmentTwo, String valueOfSegmentThree){
    this->valueOfSegmentOne=valueOfSegmentOne;
    this->valueOfSegmentTwo=valueOfSegmentTwo;
    this->valueOfSegmentThree=valueOfSegmentThree;
}
void LCD::show(){
    lcd->setCursor(9,0);
    lcd->print("T:"+valueOfSegmentTwo);
    lcd->createChar(0,charmap);
    lcd->setCursor(13,0);
    //lcd->write(0);
    lcd->print("C");
    lcd->setCursor(9,1);
    lcd->print("H:"+valueOfSegmentThree);
    byte phantram[8]={0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00};
    lcd->createChar(1,phantram);
    lcd->setCursor(13,1);
    lcd->write(1);
}
void LCD::printTime(){

}
