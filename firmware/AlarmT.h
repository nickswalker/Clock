#ifndef AlarmT_H
#define AlarmT_H

#include "definitions.h"
#include "Time.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef struct{
    unsigned char schedule;
    unsigned char hour;
    unsigned char minute;
} alarm_t;

class AlarmT {
public:

    AlarmT(uint32_t packedAlarm);
    AlarmT(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute);
  
    boolean isOn();
    boolean isActiveOnDay(timeDayOfWeek_t day);
    uint8_t getTriggerHour();
    uint8_t getTriggerMinute();
    uint8_t getSchedule();
    uint32_t getIntRepresentation();

    void setOn(boolean value);
    void setActiveOnDay(timeDayOfWeek_t day, boolean value);
 
private: 
    void init(uint8_t activeAndRepeat, uint8_t hour, uint8_t minute);
    alarm_t binary;
};
 
#endif
