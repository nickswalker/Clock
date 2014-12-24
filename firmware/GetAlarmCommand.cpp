#include "BitManipulation.h"
#include "Command.h"
#include "AlarmT.h"
#include "definitions.h"
#include "GetAlarmCommand.h"

GetAlarmCommand::GetAlarmCommand(uint8_t message[]){
     alarmNumber = (AlarmNumber)message[1];      
}

void GetAlarmCommand::execute(){
    AlarmT t = AlarmT(alarmNumber);
    uint32_t alarmBinary = t.getIntRepresentation();
    uint8_t bytes[4];
    BitManipulation::intToBytes(alarmBinary, bytes);
    uint8_t outMessage[6]  = { GETALARM, alarmNumber, 
                                bytes[0],bytes[1], bytes[2], bytes[3]};
    Serial.write(outMessage, sizeof(outMessage));
}
