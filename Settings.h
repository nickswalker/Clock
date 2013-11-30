//Shuttles to EPROM

#ifndef Settings_H
#define Settings_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Settings {
public:
        Settings();
        static void setTwelveHourTime(bool);
        static void setRadioAlarm(bool);
        static bool radioAlarm();
        static bool twelveHourTime();
        //primary alarm date/time/repeat schedule
        static int alarms[10][7];
};
 
#endif
