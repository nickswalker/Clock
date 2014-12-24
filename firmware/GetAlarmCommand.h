#ifndef GetAlarmCommand_H
#define GetAlarmCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"

class GetAlarmCommand: public Command {
public:
    GetAlarmCommand(uint8_t message[]);
    void execute();
    
private:
    AlarmNumber alarmNumber;
};
 
#endif
