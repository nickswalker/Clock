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
        
        void setExternalLightColor(int red, int green, int blue, bool animated);
        void runWakeSequence(int speed, int temperature);
        
        void setBrightness(byte value);
        
        void setLightColor(byte red, byte green, byte blue, bool animated);
        void rainbow(uint8_t wait);
        void blinkLight(int red, int green, int blue, int rate);
        void errorBlink();
        
private:
        void writeDotsToMatrix(bool colon, bool pmDot);
        uint32_t wheel(byte wheelPos);
        
};
 
#endif
