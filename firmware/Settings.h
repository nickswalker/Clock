#ifndef Settings_H
#define Settings_H

#include "definitions.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Settings {
public:
  static void setDefaults();
  static void set(Option option, byte value);
        
  static bool getBool(Option option);
  static uint8_t getByte(Option option);        

};
 
#endif
