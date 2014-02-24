#ifndef TimeHandler_H
#define TimeHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class TimeHandler {
public:
        void init();
        ~TimeHandler();
        String getTimeForDisplay(); 
        byte getSecond();
        byte getMinute();
        byte getHour();
        void setAlarm();
        void alarm();
private:
        bool getDateFromString(const char *str);
        bool getTimeFromString(const char *str);
};
 
#endif
