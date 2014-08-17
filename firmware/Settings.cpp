#include "Settings.h"
#include <EEPROM.h>

//Options get the first 50 bytes of EPROM
//This could be made ~8x more efficient by bit packing, but the code neccessary would be a little ugly.
void Settings::setDefaults(){
  set(DISPLAYTWENTYFOURHOURTIME, (bool)true);
  set(BLINKCOLON, (bool)true);
  //Set alarm for 6:30
  #ifdef DEBUG
    Serial.println("Settings defaults set.");
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
 

