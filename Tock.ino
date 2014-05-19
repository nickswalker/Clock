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

#include "Alarm.h"
#include "SensorHandler.h"
#include "IOHandler.h"
#include "TimeKeeper.h"
#include "AlarmsManager.h"
#include "Settings.h"

#include "definitions.h"
#include "PackingFunctions.h"

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
  //Illegitimate constructors since we can't declare in a greater scope without instantiating and we MUST have a serial connection before we can start I2C
  io.init();
  time.init();
  sensors.init();
  Serial.println("Setup complete");
  //alarms.setAlarm((AlarmNumber)1,);
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
  //If alarms are off
  if(!io.getAlarmState()){
    //Only check for alarms at the beggining of each minute
    if(time.getSecond() == 0){
      if( alarms.checkIfTimeTriggersAnyAlarm(time.getHour(),time.getMinute()) ) io.setAlarmState(true); 
      #ifdef DEBUG
        //io.setAlarmState(true);
      #endif
    }
  }
  else if(io.checkIfSnoozeButtonWasPressed()) io.setAlarmState(false);
  
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
      uint8_t message[3]  = { GETSETTING, option, Settings::getByte(option)};
      Serial.write(message, sizeof(message));
      break;
    }
    case GETALARM:
    {
      AlarmNumber alarmNumber = (AlarmNumber)message[1];
      uint32_t alarmBinary = alarms.getAlarm(alarmNumber);
      uint8_t bytes[4];
      PackingFunctions::intToFourBytes(alarmBinary, bytes);
      
      uint8_t message[6]  = { GETALARM, alarmNumber, bytes[0],bytes[1], bytes[2], bytes[3]};
      Serial.write(message, sizeof(message));
      break;
    }
    //SETALARM, ALARM NUMBER, minutes, hour, repeat, 0
    case SETALARM:
    {
     
     uint32_t alarm = PackingFunctions::fourSeperateBytesToInt(  (uint32_t)message[2], (uint32_t)message[3], (uint32_t)message[4], (uint32_t)message[5] );
      alarms.setAlarm( (AlarmNumber) message[1], alarm);
      break;
    }
    case SETTIME:
    {
      time_t tempTime = PackingFunctions::fourSeperateBytesToInt( (uint32_t)message[1], (uint32_t)message[2], (uint32_t)message[3], (uint32_t)message[4] ); 
      time.setAllTime(tempTime);
      break;
    }
    case TESTCONNECTION:
    {
      unsigned char message[]  = { TESTCONNECTION};
      Serial.write(message, sizeof(message));
      break;
    }
  }
  #ifdef DEBUG
    for(int i=0; i< sizeof(message); i++){
      //Serial.print(i);Serial.print(": ");
      //Serial.print(message[i]);
      //Serial.println();
    }
  //Serial.println();
  #endif
  
  memset(message, 0, sizeof(message)); //set all indexes to 0
  }
}
