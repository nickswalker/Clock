#ifndef SetAlarmCommand_H
#define SetAlarmCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"

class SetAlarmCommand: public Command {
public:
    SetAlarmCommand(uint8_t message[]);
    void execute();
private:
    uint32_t alarmBinary;
    AlarmNumber alarmNumber;
};
 
#endif
