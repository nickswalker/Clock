#include "definitions.h"
#include "SetSettingCommand.h"
#include "Settings.h"
#include "IOHandler.h"

extern IOHandler io;

SetSettingCommand::SetSettingCommand(uint8_t message[]){
    option = (Option)message[1];
    value = message[2];
}

void SetSettingCommand::execute(){
    Settings::set(option, value);
    if (option == BRIGHTNESS){
        io.setBrightness(value);
    }
}
