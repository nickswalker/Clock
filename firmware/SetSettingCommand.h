#ifndef SetSettingCommand_H
#define SetSettingCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"
#include "Settings.h"

class SetSettingCommand: public Command {
public:
    SetSettingCommand(uint8_t message[]);
    void execute();
private:
    Option option;
    uint8_t value;
};
 
#endif
