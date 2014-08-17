#include "PackingFunctions.h"

uint32_t PackingFunctions::fourBytesToInt(uint8_t bytes[]){
	return  (uint32_t)bytes[0] + ((uint32_t)bytes[1] << 8) + ((uint32_t)bytes[2] << 16) + ((uint32_t)bytes[3] << 24);
}
uint32_t PackingFunctions::fourSeperateBytesToInt(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3 ){
        uint8_t bytes[] = {byte0,byte1,byte2,byte3};
	return  fourBytesToInt(bytes);
}
boolean PackingFunctions::intToFourBytes(uint32_t integer, uint8_t bytes[]){
	bytes[0] = (integer >> 0);
	bytes[1] = (integer >> 8);
	bytes[2] = (integer >> 16);
	bytes[3] = (integer >> 24);
	
	return true;
}
