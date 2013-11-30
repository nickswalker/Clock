#ifndef IOHandler_H
#define IOHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class IOHandler {
public:
        IOHandler();
        ~IOHandler();
        
        void displayTime(int time);
        
        void alarmBuzz();
        
        void setExternalLightColor(int red, int green, int blue, bool animated);
        void runWakeSequence(int speed, int temperature);
        
        void setLightColor(int red, int green, int blue, bool animated);
        void cycleLight();
        void blinkLight(int red, int green, int blue, int rate);
        void errorBlink();
        
};
 
#endif
