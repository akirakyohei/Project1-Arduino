#include "LCD.h"
#include <String.h>

LCD::LCD(uint8_t rw,uint8_t enable,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,float valueOfSegmentOne, float valueOfSegmentTwo, float valueOfSegmentThree){
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
     lcd->createChar(1, degree);
}
LCD::~LCD(){

}
void LCD::update(float valueOfSegmentOne, float valueOfSegmentTwo, float valueOfSegmentThree){    
    this->valueOfSegmentOne=valueOfSegmentOne;
    this->valueOfSegmentTwo=valueOfSegmentTwo;
    this->valueOfSegmentThree=valueOfSegmentThree;
    
}
void LCD::show(){
  lcd->clear();
  lcd->setCursor(0,0);
  lcd->print("T:");
  lcd->print(round(valueOfSegmentOne));
  lcd->write(1);
  lcd->print("C");
  lcd->setCursor(9,0);
  lcd->print("S:");
  lcd->print(round(valueOfSegmentTwo));
  lcd->print("%");
  lcd->setCursor(5,1);
  lcd->print("O:");
  lcd->print(round(valueOfSegmentThree));
  lcd->print("%");
   
   /* lcd->setCursor(9,0);
    lcd->print("T:");
    lcd->print(valueOfSegmentTwo);
    lcd->createChar(0,charmap);
    lcd->setCursor(13,0);
    lcd->print("*C");
    lcd->setCursor(9,1);
    lcd->print("H:");
    lcd->print(valueOfSegmentThree);
    byte phantram[8]={0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00};
    lcd->createChar(1,phantram);
    lcd->setCursor(13,1);
    lcd->write(1);
    */
}
