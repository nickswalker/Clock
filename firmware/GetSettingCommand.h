#ifndef GetSettingCommand_H
#define GetSettingCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"
#include "Settings.h"

class GetSettingCommand: public Command {
public:
    GetSettingCommand(uint8_t message[]);
    void execute();
private:
    Option option;
};
 
#endif
