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
String bleIn = "";

//Pin Definitions
#define PIRSENSORPIN 4
#define LEDPIN 13
#define PHOTORESISTORPIN 14
#define IRLEDPIN 14

void setup()  {
  pinMode(LEDPIN, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Serial connection opened");
  //Settings::setDefaults();
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  
  Serial.println("Setup complete");
} 
byte sensorUpdateInterval = 0;
void loop()  {
  
  io.setLightColor(1,1,1, false);
  
   while (Serial.available() > 0)  {
    bleIn += char(Serial.read());
    delay(2);
  }
 
  if(bleIn.length() > 0) {
    if(bleIn.equals("AT")) Serial.println("OK");
    else if(bleIn.startsWith("DA:")) time.setDateWithString(bleIn.substring(3,14));
    else if(bleIn.startsWith("TI:")) time.setTimeWithString(bleIn.substring(3,11));
    else if(bleIn.startsWith("S:")){
      bool value = (bool)bleIn.substring(4,5).compareTo("0");
      int option = 0;
      char buffer [2];
      bleIn.substring(2,4).toCharArray(buffer, 2);
      option = atoi (buffer);
      Settings::set((Option)option, value);
    }
    //Serial.println(bleIn);
      bleIn = "";
  }
  if(io.readSnoozeButton()){
    Serial.print("y");
    io.alarmBuzz();
  }
  
  io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
  if( Settings::getBool(debugMode) && sensorUpdateInterval == 0 ){
     //Serial.println("Temp: " + sensors.readTemperature());
     //Serial.println("LL: " + sensors.readAmbientLightLevel());
  }
  
  sensorUpdateInterval++;
  
}


