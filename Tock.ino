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
#include "TimeKeeper.h"
#include "AlarmsManager.h"
#include "Settings.h"
#include "definitions.h"

//(Empty) constructors get executed immediately
SensorHandler sensors;
TimeKeeper time;
IOHandler io;
AlarmsManager alarms;

//Special definitions
#define MESSAGE_SIZE 18 //Message is capped at 18 bytes due to the BLE profile. If we try to get any more we simply get the same values on loop
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
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  Serial.println("Setup complete");
} 

void loop()  { 
  checkForAlarms();
  checkForCommands();
  
  io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  
  if(Settings::getBool(AUTOBRIGHTNESS)){
    io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
  }
  
}
void checkForAlarms(){
  
  if(!io.getAlarmState()){
    if(time.getSecond() == 0){
      if( time.getMinute() == 30 && time.getHour() == 6 ) io.setAlarmState(true); 
      #ifdef DEBUG
        if(time.getSecond() == 0) io.setAlarmState(true);
      #endif
    }
    if(io.checkIfSnoozeButtonWasPressed()) io.setAlarmState(true);
  }
  if(io.checkIfSnoozeButtonWasPressed()) io.setAlarmState(false);
  
}

void checkForCommands(){
  while (Serial.available() > 0)  {
    Serial.setTimeout(100);
    Serial.readBytes((char *)message,sizeof(message));
  }
   //First bit is the command bit. We can assume that the buffer is niled out if this bit is 0
   if(message[0] > 0) {
    switch((Command)message[0]){
     case SETLIGHTCOLOR:{
       int r = message[1];
       int g = message[2];
       int b = message[3];
       io.setLightColor(r,g,b,0);
       break;
     }
     case SETSETTING:{
      Option option = (Option)message[1];
      uint8_t value = message[2];
      Settings::set(option, value);
      if(option == BRIGHTNESS) io.setBrightness(value);
      break;
    }
    case GETSETTING:
    {
      Option option = (Option)message[1];
      Serial.println (Settings::getBool(option) );
      break;
    }
    case GETALARM:
    {
      AlarmNumber alarmNumber = (AlarmNumber)message[1];
      Alarm tempAlarm = alarms.getAlarm(alarmNumber);
      uint32_t alarmBinary = tempAlarm.getBinaryRepresentation();
      
      unsigned char byte1 = (alarmBinary >> 0);
      unsigned char byte2 = (alarmBinary >> 8);
      unsigned char byte3 = (alarmBinary >> 16);
      unsigned char byte4 = (alarmBinary >> 24);
      
      unsigned char message[]  = { byte1, byte2, byte3, byte4};
      Serial.write(message, 4);
      break;
    }
    case SETTIME:
    {
      time_t tempTime = (uint32_t)message[1] + ((uint32_t)message[2] << 8) + ((uint32_t)message[3] << 16) + ((uint32_t)message[4] << 24); 
      time.setAllTime(tempTime);
      break;
    }
    case TESTCONNECTION:
    {
      Serial.println("OK");
      break;
    }
  }
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
}
