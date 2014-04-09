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
    
    if (TimeHandler::getDateFromString(__DATE__) && TimeHandler::getTimeFromString(__TIME__)){
      Serial.println("DS1307 stopped. Starting system time with compile time");
      //This starts the local time object
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


void TimeHandler::setDateWithString(String dateInformation){
  char dateBuf[50];
  dateInformation.toCharArray(dateBuf, 50);
   if (this->getDateFromString(dateBuf)){
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
void TimeHandler::setTimeWithString(String timeInformation){
 char timeBuf[50];
  timeInformation.toCharArray(timeBuf, 50); 
   if (this->getTimeFromString(timeBuf)){
      setTime(tm.Hour, tm.Minute, tm.Second, tm.Day, tm.Month, tm.Year);
      if (RTC.chipPresent()) {
        Serial.println("DS1307 was set with string.");
        //This writes time to the chip
        RTC.write(tm);
      } 
      else {
        Serial.println("DS1307 fatal communication error");
      }
   }
}
//Helpers to set compile time defaults
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

bool TimeHandler::getDateFromString(const char *str){
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
bool TimeHandler::getTimeFromString(const char *str){
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}



