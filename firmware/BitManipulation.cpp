#include "BitManipulation.h"

//0th index is the least significant byte
uint32_t BitManipulation::bytesToInt(uint8_t bytes[]){
    return  (uint32_t)bytes[0] +
            ((uint32_t)bytes[1] << 8) +
	    ((uint32_t)bytes[2] << 16) +
	    ((uint32_t)bytes[3] << 24);
}

//Little endian: first byte is least significant.
uint32_t BitManipulation::separateBytesToInt(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3 ){
    uint8_t bytes[] = {byte0,byte1,byte2,byte3};
    return  bytesToInt(bytes);
}

//0th index of bytes will contain the least significant byte.
boolean BitManipulation::intToBytes(uint32_t integer, uint8_t bytes[]){
    bytes[0] = integer;
    bytes[1] = integer >> 8;
    bytes[2] = integer >> 16;
    bytes[3] = integer >> 24;

    return true;
}

uint8_t BitManipulation::setBit(uint8_t integer, int i, boolean value ){
    int shifted = (int)value << i;
    int mask = ~(shifted);
    return (integer & mask) | (shifted);
}

//Returns true if the i-th bit is 1.
//i is 0 indexed
boolean BitManipulation::checkBit(uint8_t integer, int i){
    int mask = 1 << i;
    return (integer & mask) != 0;
}
