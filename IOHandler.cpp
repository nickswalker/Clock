#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

#include "IOHandler.h"
#include "Settings.h"

Adafruit_7segment matrix = Adafruit_7segment();

void IOHandler::init(){
  matrix.begin(0x70);
  matrix.setBrightness(0);
}

void IOHandler::displayTime(unsigned time, byte second){
  bool pmDot = false;
  bool colon = false;
  if( Settings::displayTwelveHourTime() ){
    if(time>1259){
      time -= 1200;
      pmDot = true;
    }
  }  
  matrix.print(time);
  if( Settings::blinkColon() && second%2 == 0 ) colon = true;
  this->writeDotsToMatrix(colon, pmDot);
  matrix.writeDisplay();
  Serial.println(time);
}
void IOHandler::alarmBuzz(){
  tone(2000, 13);
}
void writeDotsToMatrix(bool colon, bool pmDot)  {
  byte bitmask;
  if (colon && pmDot) bitmask = 6;
  else if (colon && !pmDot) bitmask = 2;
  else if (!colon && pmDot) bitmask = 4;
  matrix.writeDigitRaw(2, bitmask);
}
