#ifndef Alarm_H
#define Alarm_H

#include "definitions.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef enum WeekBits{
  SUNDAY = 1 << 1,
  MONDAY = 1 << 2,
  TUESDAY = 1 << 3,
  WEDNESDAY = 1 << 4,
  THURSDAY = 1 << 5,
  FRIDAY = 1 << 6,
  SATURDAY = 1 << 7    
};

typedef struct{
  uint8_t activeAndRepeatSchedule;
  uint8_t hour;
  uint8_t minute;
} alarm;

class Alarm {
public:

  Alarm();
  Alarm(uint32_t packedAlarm);
  Alarm(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute);
  
  boolean isActive();
  boolean isActiveOnDay(int day);
  uint8_t getTriggerHour();
  uint8_t getTriggerMinute();
  uint32_t getBinaryRepresentation();

  void setActive();
  void setActiveOnDay(int day);
 
private:        
  boolean testIfDayMatches(int day, byte weekBitmask);        
  alarm binaryRepresentation;
};
 
#endif
