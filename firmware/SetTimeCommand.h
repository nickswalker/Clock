#ifndef SetTimeCommand_H
#define SetTimeCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"

class SetTimeCommand: public Command {
public:
    SetTimeCommand(uint8_t message[]);
    void execute();
private:
    uint32_t timeValue;
};
 
#endif
