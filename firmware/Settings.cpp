#include "Settings.h"
#include <EEPROM.h>

#define ALARMSTARTBYTE 51

//Options get the first 50 bytes of EPROM.
//The remaining is left for alarms (3 bytes each)
void Settings::setDefaults(){
  set(DISPLAYTWENTYFOURHOURTIME, (bool)true);
  set(BLINKCOLON, (bool)true);
  //Set alarm for 6:30
  #ifdef DEBUG
    Serial.println("Default settings set.");
  #endif
}

/* = Setters
--------------------------------------------------------------*/
void Settings::set(Option option, byte value){
  EEPROM.write(option, value);
}

/* = Getters
--------------------------------------------------------------*/
bool Settings::getBool(Option option){
  return (bool)EEPROM.read(option);
}

uint8_t Settings::getByte(Option option){
  return EEPROM.read(option);
}

//Alarms are given addresses in contiguous blocks of three bytes.
uint8_t Settings::getAlarmMinuteAddress(AlarmNumber alarmNumber){

  return ALARMSTARTBYTE + (alarmNumber * 3);

}

uint8_t Settings::getAlarmHourAddress(AlarmNumber alarmNumber){
  return ALARMSTARTBYTE + (alarmNumber * 3) + 1;

}

uint8_t Settings::getAlarmRepeatAddress(AlarmNumber alarmNumber){
  return ALARMSTARTBYTE + (alarmNumber * 3) + 2;
}

