#include "Settings.h"
#include <EEPROM.h>

void Settings::setDefaults(){
  set(debugMode, (bool)true);
  set(displayTwelveHourTime, (bool)true);
  set(blinkColon, (bool)true);
  Serial.println("Settings defaults set.");
}

/* = Setters
--------------------------------------------------------------*/
void Settings::set(Option option, bool value){
  EEPROM.write(option, value);
}
void Settings::set(Option option, byte value){
  EEPROM.write(option, value);
}

/* = Getters
--------------------------------------------------------------*/
bool Settings::getBool(Option option){
  return (bool)EEPROM.read(option);
}

byte Settings::getByte(Option option){
  return EEPROM.read(option);
}
 

