#include "Alarm.h"

Alarm::Alarm(){
 this->binaryRepresentation.hour = 0;
 this->binaryRepresentation.minute = 0;
 this->binaryRepresentation.activeAndRepeatSchedule = 0;
  
}
Alarm::Alarm(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute){
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

uint32_t Alarm::getBinaryRepresentation(){
  uint32_t tempAlarm = (uint32_t)0 + ((uint32_t)this->binaryRepresentation.minute << 8) + ((uint32_t)this->binaryRepresentation.hour << 16) + ((uint32_t)this->binaryRepresentation.activeAndRepeatSchedule << 24);
  return tempAlarm; 
}
