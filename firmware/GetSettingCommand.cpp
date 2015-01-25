#include "definitions.h"
#include "GetSettingCommand.h"
#include "Settings.h"
#include "IOHandler.h"

extern IOHandler io;

GetSettingCommand::GetSettingCommand(uint8_t message[]){
    option = (Option)message[1];
}

void GetSettingCommand::execute(){
    uint8_t outMessage[] = {GETSETTING, option, Settings::getByte(option)};
    Serial.write(outMessage, 3);
}
