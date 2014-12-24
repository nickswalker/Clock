#include <Arduino.h>
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

#include "AlarmT.h"
#include "SensorHandler.h"
#include "IOHandler.h"
#include "TimeKeeper.h"
#include "AlarmsManager.h"
#include "Settings.h"
#include "Command.h"

#include "SetLightColorCommand.h"
#include "SetAlarmCommand.h"
#include "GetAlarmCommand.h"
#include "SetTimeCommand.h"

#include "definitions.h"
#include "BitManipulation.h"

//(Empty) constructors get executed immediately
SensorHandler sensors;
TimeKeeper time;
IOHandler io;
AlarmsManager alarms;

//Special definitions
#define MESSAGE_SIZE 18 //Message is capped at 18 bytes due to the BLE profile. If we try to get any more we simply get the same values on loop (ring buffer)
#define DEBUG

//Global vars
unsigned long startTime;
uint8_t message[MESSAGE_SIZE];


void setup()  {
    pinMode(LEDPIN, OUTPUT); 
    Serial.begin(9600);
    #ifdef DEBUG
        Settings::setDefaults();
    #endif
    
    //Illegitimate constructors since we can't declare in a greater scope without instantiating
    //and we MUST have a serial connection before we can start I2C
    io.init();
    time.init();
    sensors.init();
    
    Serial.println("Setup complete");
    
} 

void loop()  { 
    checkForAlarms();
    checkForCommands();
  
    io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  
    if (Settings::getBool(AUTOBRIGHTNESS)){
      io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
    }
  
}

void checkForAlarms(){
  //If alarms are off
    if (!io.getAlarmState()){
      //Only check for alarms at the beggining of each minute
      if (time.getSecond() == 0){
      if (alarms.checkIfTimeTriggersAnyAlarm(time.getHour(),time.getMinute()) ){
          io.setAlarmState(true); 
      }
      #ifdef DEBUG
          io.setAlarmState(true);
      #endif
    }
  }
  else if(io.checkIfSnoozeButtonWasPressed()){
    io.setAlarmState(false);
  }
  
}

void checkForCommands(){
  while (Serial.available() > 0)  {
      Serial.setTimeout(100);
      Serial.readBytes((char *)message,sizeof(message));
  }
  Command* command = Command::construct(message);
  Command& dereferenced = *command;
  dereferenced.execute();
  delete command;
  #ifdef DEBUG
      for(int i=0; i< sizeof(message); i++){
          Serial.print(i);Serial.print(": ");
          Serial.print(message[i]);
          Serial.println();
      }
      Serial.println();
  #endif

  memset(message, 0, sizeof(message)); //set all indexes to 0
}
