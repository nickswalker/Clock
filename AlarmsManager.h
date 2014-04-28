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
  Alarm getAlarm(AlarmNumber alarmNumber);
  AlarmNumber getNextEmptyAlarm();
  void clearAlarm(AlarmNumber alarmNumber);
private:        

};
 
#endif
