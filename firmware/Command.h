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
    SETTIME = 1,
    SETLIGHTCOLOR = 2,
    GETLIGHTCOLOR = 3,
    SETALARM = 4,
    GETALARM = 5,
    SETSETTING = 6,
    GETSETTING = 7,
    RESET = 254,
    TESTCONNECTION = 255
} CommandFlag;

class Command {
public:
    static Command* parse(uint8_t message[]);
    virtual void execute() =0;
    
};
 
#endif
