//Shuttles to EPROM

#ifndef Settings_H
#define Settings_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef enum Option{
  blinkColon,
  displayTwelveHourTime,
  brightness,
  alarmVolume,
  debugMode
};

class Settings {
public:
        static void setDefaults();
        static void set(Option option, bool value);
        static void set(Option option, byte value);
        
        static bool getBool(Option option);
        static byte getByte(Option option);
        
        static Option optionFromString(String string);

};
 
#endif
