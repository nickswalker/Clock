#include "SensorHandler.h"
#include <dht11.h>

#define DHT11PIN 2

void SensorHandler::init(){
  Serial.println("SensorHandler setup complete");
}
SensorHandler::~SensorHandler(){
  
}
int SensorHandler::readAmbientLightLevel(){
  return 0.0;
}

int SensorHandler::readTemperature(){
  tempSensor.read(DHT11PIN);
return this->fahrenheit((int)tempSensor.temperature);
}

int SensorHandler::fahrenheit(int celcius)
{
  return (celcius * 18 + 5)/10 + 32;
}

