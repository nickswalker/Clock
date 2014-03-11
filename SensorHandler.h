#ifndef SensorHandler_H
#define SensorHandler_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define photoResistorPin 14

#include <dht11.h>

class SensorHandler {
public:
        void init();
        int readTemperature();
        int readAmbientLightLevel();
private:
  int fahrenheit(int celcius);
  dht11 tempSensor;
};
 
#endif
