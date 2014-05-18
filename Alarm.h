#ifndef Alarm_H
#define Alarm_H

#include "definitions.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif



class Alarm {
public:

  Alarm();
  Alarm(uint32_t packedAlarm);
  Alarm(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute);
  
  void init(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute);
  
  boolean isActive();
  boolean isActiveOnDay(int day);
  uint8_t getTriggerHour();
  uint8_t getTriggerMinute();
  uint32_t getBinaryRepresentation();

  void setActive();
  void setActiveOnDay(int day);
 
private:        
  boolean testIfDayMatches(int day, byte weekBitmask);        
  alarm_t binaryRepresentation;
};
 
#endif
