#include "Alarm.h"
#include "PackingFunctions.h"

Alarm::Alarm(){
 init(0,0,0);
}
Alarm::Alarm(uint32_t packedAlarm){
 uint8_t bytes[4];
 PackingFunctions::intToFourBytes(packedAlarm, bytes);
 init(bytes[2],bytes[1],bytes[0]);
}
Alarm::Alarm(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute){
    init(activeAndRepeat, hour, minute);
}


void Alarm::init(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute){
 this->binaryRepresentation.hour = hour;
 this->binaryRepresentation.minute = minute;
 this->binaryRepresentation.activeAndRepeatSchedule = activeAndRepeat;
}


boolean Alarm::isActive(){
  return true;
}
boolean Alarm::isActiveOnDay(int day){
 return false;
 
}

void Alarm::setActive(){
}
void Alarm::setActiveOnDay(int day){
 
}

uint8_t Alarm::getTriggerHour(){
  return this->binaryRepresentation.hour; 
}

uint8_t Alarm::getTriggerMinute(){
  return this->binaryRepresentation.minute; 
}
//Little Endian
//00000000 REPEAT HOUR MINUTE
//Byte3    Byte2  Byte1 Byte0
uint32_t Alarm::getBinaryRepresentation(){
  uint32_t tempAlarm = ((uint32_t)this->binaryRepresentation.minute) + ((uint32_t)this->binaryRepresentation.hour << 8) + ((uint32_t)this->binaryRepresentation.activeAndRepeatSchedule << 16);
  return tempAlarm; 
}
