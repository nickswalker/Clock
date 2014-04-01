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

//Empty constructors get executed
SensorHandler sensors;
TimeHandler time;
IOHandler io;
String bleIn = "";

//Pin Definitions

#define LEDPIN 13
#define PHOTORESISTORPIN 14
#define IRLEDPIN 14

void setup()  {
  pinMode(LEDPIN, OUTPUT); 
  Serial.begin(9600);
  //Settings::setDefaults();
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  
  Serial.println("Setup complete");
} 
byte sensorUpdateInterval = 0;
void loop()  { 
  
  //You only get 18 chars
   while (Serial.available() > 0)  {
     
     Serial.setTimeout(100); // 100 millisecond timeout
     bleIn = Serial.readString();
    
  }
 
  if(bleIn.length() > 0) {
    if(bleIn.startsWith("AT")) Serial.println("OK");
    else if(bleIn.startsWith("DA:")) time.setDateWithString(bleIn.substring(3,14));
    else if(bleIn.startsWith("TI:")) time.setTimeWithString(bleIn.substring(3,11));
    else if(bleIn.startsWith("L:")) {
      int r = IOHandler::intFromHexString(bleIn.substring(2,4));
      int g = IOHandler::intFromHexString(bleIn.substring(4,6));
      int b = IOHandler::intFromHexString(bleIn.substring(6,8));
      io.setLightColor(r,g,b,0);
    }
    // First  digits = option integer
    // Second digit = bool value
    // If string is only one digit, query and return the value of the setting
    else if(bleIn.startsWith("S:")){
      
      Option option = Settings::optionFromString( bleIn.substring(2,3) );
     
   
      if (bleIn.length() > 3){ 
        bool value = bleIn.substring(3,4).equals("1");
        Settings::set(option, value);
      }
      else Serial.println (Settings::getBool((Option)option) );
    }
    //Serial.println(bleIn);
      bleIn = "";
  }
  if(io.readSnoozeButton()){
    Serial.println("Button");
    io.alarmBuzz();
  }
  if(sensors.personIsPresent()) digitalWrite(LEDPIN, HIGH);
  else digitalWrite(LEDPIN, LOW);
  
  io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
  if( Settings::getBool(debugMode) && sensorUpdateInterval == 0 ){
     //Serial.println("Temp: " + sensors.readTemperature());
     //Serial.println("LL: " + sensors.readAmbientLightLevel());
  }
  
  sensorUpdateInterval++;
  
}


