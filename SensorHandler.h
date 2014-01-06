#ifndef SensorHandler_H
#define SensorHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <dht11.h>

class SensorHandler {
public:
        void init();
        ~SensorHandler();
        int readTemperature();
        int readAmbientLightLevel();
private:
  int fahrenheit(int celcius);
  dht11 tempSensor;
};
 
#endif
