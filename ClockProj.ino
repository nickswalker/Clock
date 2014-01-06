//#include <IRremote.h>
//#include <IRremoteInt.h>
#include <Time.h>
#include <dht11.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
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
int led = 13;

void setup()  {
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  Serial.println("SETUP COMPLETE");
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  Settings::setDefaults();
} 

void loop()  {
  io.displayTime(time.getTimeForDisplay(), time.getSecond());
  delay(100);
  
}

