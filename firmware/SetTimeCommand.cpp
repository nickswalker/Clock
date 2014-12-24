#include "definitions.h"
#include "SetTimeCommand.h"
#include "BitManipulation.h"
#include "TimeKeeper.h"

extern TimeKeeper time;

SetTimeCommand::SetTimeCommand(uint8_t message[]){
    timeValue = BitManipulation::separateBytesToInt( message[1], message[2], message[3], message[4] );
}

void SetTimeCommand::execute(){
    time.setAllTime(timeValue);
}
