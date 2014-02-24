//Shuttles to EPROM

#ifndef Settings_H
#define Settings_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

//This needs to be rewritten to use an enum and a single method. DRY and all.
class Settings {
public:
        static void setDefaults();
        
        static void setBlinkColon(bool);
        static void setRadioAlarm(bool);
        static void setDisplayTwelveHourTime(bool);
        static void setProximityTurnOnLight(bool);
        static void setBrightness(byte);
        static void setDebugLogging(bool);
        
        static bool blinkColon();
        static bool radioAlarm();
        static bool displayTwelveHourTime();
        static bool proximityTurnOnLight();
        static byte brightness();
        static bool debugLogging();
        
        //primary alarm date/time/repeat schedule
        static int alarms[10][7];
};
 
#endif
