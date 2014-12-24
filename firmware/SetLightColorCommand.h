#ifndef SetLightColorCommand_H
#define SetLightColorCommand_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Command.h"

class SetLightColorCommand: public Command {
public:
    SetLightColorCommand(uint8_t message[]);
    void execute();
private:
    int r;
    int g;
    int b;
};
 
#endif
