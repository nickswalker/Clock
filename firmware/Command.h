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

typedef enum {
    SETDATE = 1,
    SETTIME = 2,
    SETLIGHTCOLOR = 3,
    GETLIGHTCOLOR = 4,
    SETALARM = 5,
    GETALARM = 6,
    SETSETTING = 7,
    GETSETTING = 8,
    RESET = 254,
    TESTCONNECTION = 255
} CommandFlag;

class Command {
public:
    static Command* construct(uint8_t message[]);
    virtual void execute() =0;
    
};
 
#endif
