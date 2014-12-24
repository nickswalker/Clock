#ifndef AlarmsManager_H
#define AlarmsManager_H

#include "definitions.h"
#include "AlarmT.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef enum{
    ALARM1 = 1,
    ALARM2 = 2,
    ALARM3 = 3,
    ALARM4 = 4,
    ALARM5 = 5,
    ALARM6 = 6,
    ALARM7 = 7
} AlarmNumber;

class AlarmsManager {
public:
    AlarmNumber getNextEmptyAlarm();
    void clearAlarm(AlarmNumber alarmNumber);
    boolean checkIfTimeTriggersAnyAlarm(uint8_t hour, uint8_t minute);
    void setAlarm(AlarmNumber alarmNumber, AlarmT alarm);
    AlarmT getAlarm(AlarmNumber alarmNumber);
private:        

};
 
#endif
