#ifndef TimeHandler_H
#define TimeHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class TimeHandler {
public:
        TimeHandler();
        ~TimeHandler();
        int getTimeForDisplay(); 
        
        void setAlarm();
        void alarm();
      
};
 
#endif
