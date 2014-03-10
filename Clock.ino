 //#include <IRremote.h>
//#include <IRremoteInt.h>
#include <Time.h>
#include <dht11.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <EEPROM.h>
//Arduino will only check this file for libraries to include, so we need to pull them all in here

#include "SensorHandler.h"
#include "IOHandler.h"
#include "TimeHandler.h"
#include "Settings.h"

//Empty constructors
SensorHandler sensors;
TimeHandler time;
IOHandler io;

//Pin Definitions
#define ledPin 13
#define photoResistorPin 14

void setup()  {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Serial connection opened");
  Settings::setDefaults();
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  
  Serial.println("Setup complete");
} 

void loop()  {
  
  io.setLightColor(1,1,1, false);
  if(io.readSnoozeButton()){
    Serial.print("y");
    io.alarmBuzz();
  }
  
  io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
  if(Settings::debugLogging()){
     //Serial.println("Temp: " + sensors.readTemperature());
     //Serial.println("Light level: " + sensors.readAmbientLightLevel());
  }
  
}

