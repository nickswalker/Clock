#include "Settings.h"
#include <EEPROM.h>

void Settings::setDefaults(){
  set(debugMode, (bool)true);
  set(displayTwelveHourTime, (bool)false);
  set(blinkColon, (bool)true);
  Serial.println("Settings defaults set.");
}

void Settings::set(Option option, bool value){
  EEPROM.write(option, value);
}
void Settings::set(Option option, byte value){
  EEPROM.write(option, value);
}


bool Settings::getBool(Option option){
  return (bool)EEPROM.read(option);
}

byte Settings::getByte(Option option){
  return EEPROM.read(option);
}
 
