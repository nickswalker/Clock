#include "Settings.h"
#include <EEPROM.h>

void Settings::setDefaults(){
  setBlinkColon(true);
  setRadioAlarm(false);
  setDisplayTwelveHourTime(true);
  setProximityTurnOnLight(true);
}

void Settings::setBlinkColon(bool value){
  EEPROM.write(1, value);
}
void Settings::setRadioAlarm(bool value){
  EEPROM.write(2, value);
}
void Settings::setDisplayTwelveHourTime(bool value){
  EEPROM.write(3, value);
}
void Settings::setProximityTurnOnLight(bool value){
  EEPROM.write(4, value);
}
bool Settings::blinkColon(){
  return (bool)EEPROM.read(1);
}
bool Settings::radioAlarm(){
  return (bool)EEPROM.read(2);
}
bool Settings::displayTwelveHourTime(){
  return (bool)EEPROM.read(3);
}
bool Settings::proximityTurnOnLight(){
  return (bool)EEPROM.read(4);
}
 
