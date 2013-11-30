#include <IRremote.h>
#include <IRremoteInt.h>
#include <EEPROM.h>
#include <Time.h>
#include <dht11.h>
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Wire.h>
//Arduino will only check this file for libraries to include, so we need to pull them all in here

#include "SensorHandler.h"
#include "IOHandler.h"
#include "TimeHandler.h"

SensorHandler sensors;
IOHandler io;


int led = 13;

void setup()  {
  pinMode(led, OUTPUT); 
  delay(2000); 
  Serial.begin(9600);
  Serial.println("SETUP COMPLETE"); 

} 

void loop()  {
  //This really needs to be up at the top with the rest of the handler initialization, but the constructor for the time shell can't
  //be called before setup for some reason.  
  TimeHandler time;
  io.displayTime(time.getTimeForDisplay());
  
  delay(2000);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second  
}

