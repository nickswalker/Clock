#include "TimeHandler.h"
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Time.h>

tmElements_t tm;

void TimeHandler::init(){
  //Read from the RTC and set the our soft clock based off of it, if not set a default
  //The RTC library is fully static. Might want to write a new version? Investigate why.
  if (RTC.read(tm)) {
    //These members are capitalized too... Another reason to consider revising.
    setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tm.Year);
    Serial.println("DN1307 read and system time set");
  }
  else {
    
    if (TimeHandler::getDate(__DATE__) && TimeHandler::getTime(__TIME__)){
      Serial.println("DS1307 stopped. Starting system time with compile time");
      setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tm.Year);
      if (RTC.chipPresent()) {
        Serial.println("DS1307 was restarted with compile time");
        RTC.write(tm);
      } 
      else {
        Serial.println("DS1307 fatal communication error");
      }
    }
    
  }
  setSyncProvider(RTC.get);
  Serial.println("TimeHandler setup complete");
}
TimeHandler::~TimeHandler(){
   Serial.println("Deconstructed");
}
unsigned int TimeHandler::getTimeForDisplay(){
  //four digit number.
  return (hour() *100) + minute();
}
byte TimeHandler::getSecond(){
  //four digit number.
  return second();
}

void TimeHandler::setAlarm(){}
void TimeHandler::alarm(){}


//Helpers to set compile time defaults
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

bool TimeHandler::getDate(const char *str){
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
bool TimeHandler::getTime(const char *str){
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}



