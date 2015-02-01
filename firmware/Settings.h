#ifndef Settings_H
#define Settings_H

#include "definitions.h"
#include "AlarmsManager.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef enum {
    DISPLAYTWENTYFOURHOURTIME = 1,
    BLINKCOLON = 20,
    AUTOBRIGHTNESS = 3,
    BRIGHTNESS = 4
} Option;

class Settings {
public:
  static void setDefaults();
  static void set(Option option, byte value);
        
  static bool getBool(Option option);
  static uint8_t getByte(Option option);

  static uint8_t getAlarmMinuteAddress(AlarmNumber alarmNumber);
  static uint8_t getAlarmHourAddress(AlarmNumber alarmNumber);
  static uint8_t getAlarmRepeatAddress(AlarmNumber alarmNumber);

};
 
#endif
