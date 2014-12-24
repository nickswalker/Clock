#ifndef BitManipulation_H
#define BitManipulation_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class BitManipulation {
public:

    static uint32_t bytesToInt(uint8_t bytes[]);
    static uint32_t separateBytesToInt(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3 );
    static boolean intToBytes(uint32_t integer, uint8_t bytes[]);
    static boolean checkBit(uint8_t integer, int i);
    static uint8_t setBit(uint8_t integer, int i, boolean value);

};

#endif
