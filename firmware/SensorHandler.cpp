#include "SensorHandler.h"
#include "definitions.h"
#include <dht11.h>

void SensorHandler::init(){
  #ifdef DEBUG
    Serial.println("SensorHandler setup complete");
  #endif
}

int SensorHandler::readAmbientLightLevel(){
  return analogRead(PHOTORESISTORPIN);
}



