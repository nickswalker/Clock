#include "SensorHandler.h"
#include "pin_definitions.h"
#include <dht11.h>

void SensorHandler::init(){
  Serial.println("SensorHandler setup complete");
}

int SensorHandler::readAmbientLightLevel(){
  return analogRead(PHOTORESISTORPIN);
}

boolean SensorHandler::personIsPresent(){
  return digitalRead(PIRSENSORPIN); 
}

/* = Temperature
--------------------------------------------------------------*/

int SensorHandler::readTemperature(){
  tempSensor.read(DHT11PIN);
  return this->fahrenheit((int)tempSensor.temperature);
}

int SensorHandler::fahrenheit(int celcius)
{
  return (celcius * 18 + 5)/10 + 32;
}

