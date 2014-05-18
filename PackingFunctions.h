#ifndef PackingFunctions_H
#define PackingFunctions_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class PackingFunctions {
public:

static uint32_t fourBytesToInt(uint8_t bytes[]);
static uint32_t fourSeperateBytesToInt(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3 );
static boolean intToFourBytes(uint32_t integer, uint8_t bytes[]);
  
private:        

};

#endif
