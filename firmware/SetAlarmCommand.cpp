#include "definitions.h"
#include "SetAlarmCommand.h"
#include "BitManipulation.h"
#include "AlarmT.h"
#include "AlarmsManager.h"

extern AlarmsManager alarms;

SetAlarmCommand::SetAlarmCommand(uint8_t message[]){
    alarmNumber = (AlarmNumber) message[1];
    alarmBinary = BitManipulation::separateBytesToInt(  message[2], message[3], message[4], message[5] );

}

void SetAlarmCommand::execute(){
    AlarmT alarm = AlarmT(alarmBinary);
    alarms.setAlarm( alarmNumber, alarm);
}
