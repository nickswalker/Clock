#include "definitions.h"
#include "Command.h"
#include "IOHandler.h"
#include <Arduino.h>

#include "SetLightColorCommand.h"
#include "SetAlarmCommand.h"
#include "SetSettingCommand.h"
#include "GetAlarmCommand.h"
#include "GetSettingCommand.h"
#include "SetTimeCommand.h"

Command* Command::construct(uint8_t message[]){
    Command* returnCommand = NULL;
    switch((CommandFlag)message[0]){
        case SETLIGHTCOLOR:{
            returnCommand = new SetLightColorCommand(message);
            break;
        }
        case SETSETTING:{
            returnCommand = new SetSettingCommand(message);
            break;
        }
        case GETSETTING:{
            returnCommand = new GetSettingCommand(message);
            break;
        }
        case GETALARM:{
            returnCommand = new GetAlarmCommand(message);
            break;
        }
        //SETALARM, ALARM NUMBER, minutes, hour, repeat, 0
        case SETALARM:{
            returnCommand = new SetAlarmCommand(message);
            break;
        }
        case SETTIME:{
            returnCommand = new SetTimeCommand(message);
            break;
        }
        case TESTCONNECTION:
        {
            uint8_t outMessage[] = {TESTCONNECTION};
            Serial.write(outMessage, sizeof(outMessage));
            break;
        }
    }
    return returnCommand;

}
