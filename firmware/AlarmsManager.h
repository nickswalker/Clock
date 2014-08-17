#ifndef AlarmsManager_H
#define AlarmsManager_H

#include "definitions.h"
#include "Alarm.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


class AlarmsManager {
public:

  uint32_t getAlarm(AlarmNumber alarmNumber);
  AlarmNumber getNextEmptyAlarm();
  void clearAlarm(AlarmNumber alarmNumber);
  boolean checkIfTimeTriggersAnyAlarm(uint8_t hour, uint8_t minute);
  void setAlarm(AlarmNumber alarmNumber, uint32_t alarmBinary);
private:        

};
 
#endif
