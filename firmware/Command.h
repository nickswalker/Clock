#ifndef Command_H
#define Command_H
 
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "SensorHandler.h"
#include "IOHandler.h"
#include "AlarmsManager.h"
#include "TimeKeeper.h"

class Command {
public:
    static Command* parse(uint8_t message[]);
    virtual void execute() =0;
    
};
 
#endif
