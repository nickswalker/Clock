#include "TimeHandler.h"
#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Time.h>

tmElements_t tm;

void TimeHandler::init(){
  //Read from the RTC and set the our soft clock based off of it
  
  if (RTC.read(tm)) {
    setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tm.Year);
    Serial.println("DN1307 read and system time set");
  }
  //Time couldn't be read
  else {
    //Try parsing time from compile-time data
    if (TimeHandler::parseDateFromString(__DATE__, tm) && TimeHandler::parseTimeFromString(__TIME__, tm)){
      Serial.println("DS1307 stopped. Starting system time with compile time");
      setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tm.Year);
      if (RTC.chipPresent()) {
        Serial.println("DS1307 was restarted with compile time");
        //This writes time to the chip
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
 
byte TimeHandler::getSecond(){
  return second();
}
byte TimeHandler::getMinute(){
  return minute();
}
byte TimeHandler::getHour(){
  return hour();
}


//Helpers to set compile time defaults
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/* = Parsers
--------------------------------------------------------------*/
boolean TimeHandler::parseDateFromString(const char *str, tmElements_t tm){
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

boolean TimeHandler::parseTimeFromString(const char *str, tmElements_t tm){
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}



