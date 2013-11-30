#include <IRremote.h>
#include <IRremoteInt.h>

#include "IOHandler.h"

IOHandler::IOHandler(){

}

void IOHandler::displayTime(int time){
  //This will drive the 7 seg.
  Serial.println(time);
}
void IOHandler::alarmBuzz(){
  tone(2000, 13);
}
