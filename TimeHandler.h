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
        String getTimeForDisplay(); 
        byte getSecond();
        byte getMinute();
        byte getHour();
        void setAlarm();
        void alarm();
        void setTimeWithString(String timeInformation);
        void setDateWithString(String dateInformation);
        bool getDateFromString(const char *str);
        bool getTimeFromString(const char *str);
private:

};
 
#endif
