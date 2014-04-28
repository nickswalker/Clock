#include "Settings.h"
#include <EEPROM.h>

void Settings::setDefaults(){
  set(DEBUGMODE, (bool)true);
  set(DISPLAYTWENTYFOURHOURTIME, (bool)true);
  set(BLINKCOLON, (bool)true);
  Serial.println("Settings defaults set.");
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
 

