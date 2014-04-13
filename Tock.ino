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
#include "pin_definitions.h"

//(Empty) constructors get executed immediately
SensorHandler sensors;
TimeHandler time;
IOHandler io;

//Special definitions
#define MESSAGE_SIZE 18 //Message is capped at 18 bytes due to the BLE profile. If we try to get any more we simply get the same values on loop

//Global vars
unsigned long startTime;
byte message[MESSAGE_SIZE];


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

void loop()  { 
  checkForAlarms();
  checkForCommands();
  
  io.displayTime(time.getHour(), time.getMinute(), time.getSecond());
  io.setBrightness(map(sensors.readAmbientLightLevel(), 0, 1024, 0, 15 ));
  
}
void checkForAlarms(){
  if(!io.getAlarmState()){
    if( time.getSecond() == 0 && time.getMinute() == 30 && time.getHour() == 6 ) io.setAlarmState(true); 
    //if(time.getSecond() == 0) io.setAlarmState(true);
  }
  if(io.checkIfSnoozeButtonWasPressed()) io.setAlarmState(false);
    
    
}
typedef enum Command{
  SETDATE = 1,
  SETTIME = 2,
  SETLIGHTCOLOR = 3,
  GETLIGHTCOLOR = 4,
  SETALARM = 5,
  GETALARM = 6,
  SETSETTING = 7,
  GETSETTING = 8,
  TESTCONNECTION =255      
};

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
        bool value = message[2];
        Settings::set(option, value);
        break;
      }
      case GETSETTING:
      {
        Option option = (Option)message[1];
        Serial.println (Settings::getBool((Option)option) );
        break;
      }
      case SETTIME:
      {
        time_t time = (uint32_t)message[1] + ((uint32_t)message[2] << 8) + ((uint32_t)message[3] << 16) + ((uint32_t)message[4] << 24); 
        RTC.set(time);
        setTime(time);
        Serial.println(time);
        break;
      }
      case TESTCONNECTION:
      {
        Serial.println("OK");
        break;
      }
    }
    for(int i=0; i< sizeof(message); i++){
      Serial.print(i);Serial.print(": ");
      Serial.print(message[i]);
      Serial.println();
    }
    Serial.println();
    memset(message, 0, sizeof(message)); //set all indexes to 0
  }
}
