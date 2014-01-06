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
        static void setDefaults();
        
        static void setBlinkColon(bool);
        static void setRadioAlarm(bool);
        static void setDisplayTwelveHourTime(bool);
        static void setProximityTurnOnLight(bool);
        
        static bool blinkColon();
        static bool radioAlarm();
        static bool displayTwelveHourTime();
        static bool proximityTurnOnLight();
        
        //primary alarm date/time/repeat schedule
        static int alarms[10][7];
};
 
#endif
