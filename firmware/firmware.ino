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
#include <ArduinoUnit.h>
//Arduino will only check this file for libraries to include, so we need to pull them all in here

#include "AlarmT.h"
#include "SensorHandler.h"
#include "IOHandler.h"
#include "TimeKeeper.h"
#include "AlarmsManager.h"
#include "Settings.h"
#include "Command.h"

#include "SetSettingCommand.h"
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
//#define DEBUG

//Global vars
unsigned long startTime;
uint8_t message[MESSAGE_SIZE];

test(setOptionCommand){
    uint8_t message[] = {0, BLINKCOLON, 0};
    SetSettingCommand command = SetSettingCommand(message);
    command.execute();
    assertEqual(Settings::getBool(BLINKCOLON),0); 
    uint8_t message2[] = {0, DISPLAYTWENTYFOURHOURTIME, 0};
   command = SetSettingCommand(message2);
    command.execute();
    assertEqual(Settings::getBool(DISPLAYTWENTYFOURHOURTIME),0);
}
test(setRetrieveAlarmsManager){
    AlarmT alarm = AlarmT(0xff, 6, 30);
    alarms.setAlarm((AlarmNumber)1, alarm);
    AlarmT alarm2 = alarms.getAlarm((AlarmNumber)1);
    assertEqual(alarm.getIntRepresentation(), alarm2.getIntRepresentation());
}
test(alarmTIntRepresentation){
    AlarmT alarm = AlarmT(0xff, 6, 30);
    AlarmT alarm2 = AlarmT(alarm.getIntRepresentation());
    assertEqual(alarm.getIntRepresentation(), alarm2.getIntRepresentation());   
}
test(alarmTConstructionFromParts){
    AlarmT alarm = AlarmT(0xff, 6, 30);
    assertEqual(alarm.getTriggerMinute(), 30);
    assertEqual(alarm.getTriggerHour(), 6);
    assertEqual(alarm.getSchedule(), 0xff);   
}
test(setAlarmCommand){
    uint8_t message[] = {0, 1, 30, 06, 0xff};
    SetAlarmCommand command = SetAlarmCommand(message);
    command.execute();
    AlarmT alarm = alarms.getAlarm((AlarmNumber)1);
    uint32_t expected = 0x00ff061e;
    assertEqual(alarm.getIntRepresentation(),expected); 
}
test(separateBytesToInt){
    uint32_t expected = 0xccdd00ff;
    uint32_t combined = BitManipulation::separateBytesToInt(0xff, 0x00, 0xdd, 0xcc);
    assertEqual(expected, combined);
}
test(intToBytes){
    uint32_t value = 0xccdd00ff;
    uint8_t bytes[4];
    BitManipulation::intToBytes(value, bytes);
    assertEqual(bytes[0], 0xff);
    assertEqual(bytes[1], 0x00);
    assertEqual(bytes[2], 0xdd);
    assertEqual(bytes[3], 0xcc);
}

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
    //Test::run();
  
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
              //io.setAlarmState(true);
          #endif
    }
  }
  else if(io.checkIfSnoozeButtonWasPressed()){
    io.setAlarmState(false);
  }
  
}

/**
  *
  */
void checkForCommands(){
  while (Serial.available() > 0)  {
      Serial.setTimeout(100);
      Serial.readBytes((char *)message,sizeof(message));
  }
  if(message[0] != 0){
      Command* command = Command::parse(message);
      if(command != NULL){
          Command& dereferenced = *command;
          dereferenced.execute();
          delete command;
      }
      #ifdef DEBUG
          for(int i=0; i< sizeof(message); i++){
              Serial.print(i);Serial.print(": ");
              Serial.print(message[i]);
              Serial.println();
          }
          Serial.println();
      #endif
  }

  memset(message, 0, sizeof(message)); //set all indexes to 0
}
