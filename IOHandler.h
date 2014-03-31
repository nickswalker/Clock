#ifndef IOHandler_H
#define IOHandler_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class IOHandler {
public:
        void init();
        
        void displayTime(byte hour, byte minute, byte second);
        void alarmBuzz();
        
        bool readSnoozeButton();
         
        void setExternalLightColor(int red, int green, int blue, bool animated);
        void runWakeSequence(int speed, int temperature);
        
        void setBrightness(byte value);
        
        void setLightColor(byte red, byte green, byte blue, bool animated);
        void blinkLight(int red, int green, int blue, int rate);
        void errorBlink();
         static int intFromHexString(String string); 
        
private:
        void writeDotsToMatrix(bool colon, bool pmDot);
       
        
};
 
#endif
