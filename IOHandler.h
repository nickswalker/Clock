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
        
        void displayTime(unsigned int time, byte second);
        
        void alarmBuzz();
        
        void setExternalLightColor(int red, int green, int blue, bool animated);
        void runWakeSequence(int speed, int temperature);
        
        void setLightColor(int red, int green, int blue, bool animated);
        void rainbow(uint8_t wait);
        void blinkLight(int red, int green, int blue, int rate);
        void errorBlink();
        
private:
        void writeDotsToMatrix(bool colon, bool pmDot);
        uint32_t wheel(byte wheelPos);
        
};
 
#endif
