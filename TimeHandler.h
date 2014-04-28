#ifndef TimeHandler_H
#define TimeHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Time.h>

class TimeHandler {
public:
  void init();
 
  uint8_t getSecond();
  uint8_t getMinute();
  uint8_t getHour();
  void setAllTime(time_t time);
  
  void setAlarm();
  void alarm();
  
private:
  boolean parseDateFromString(const char *str, tmElements_t tm);
  boolean parseTimeFromString(const char *str, tmElements_t tm);

};
 
#endif
