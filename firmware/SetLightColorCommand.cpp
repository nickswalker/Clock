#include "definitions.h"
#include "SetLightColorCommand.h"

SetLightColorCommand::SetLightColorCommand(uint8_t message[]){
    r = message[1];
    g = message[2];
    b = message[3];
}

void SetLightColorCommand::execute(){
    //We've removed the light for now...
}
