#include "SensorHandler.h"
#include <dht11.h>

#define DHT11PIN 2
#define PHOTORESISTORPIN 14

void SensorHandler::init(){
  Serial.println("SensorHandler setup complete");
}

int SensorHandler::readAmbientLightLevel(){
  return analogRead(PHOTORESISTORPIN);
}

int SensorHandler::readTemperature(){
  tempSensor.read(DHT11PIN);
  return this->fahrenheit((int)tempSensor.temperature);
}

int SensorHandler::fahrenheit(int celcius)
{
  return (celcius * 18 + 5)/10 + 32;
}

