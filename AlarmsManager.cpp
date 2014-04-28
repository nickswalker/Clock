#include "AlarmsManager.h"
#include "Alarm.h"
#include <EEPROM.h>

//Alarms start at byte 51
Alarm AlarmsManager::getAlarm(AlarmNumber alarmNumber){
  return Alarm( EEPROM.read(51+alarmNumber), EEPROM.read(51+alarmNumber +1), EEPROM.read(51+alarmNumber +2) );
  
}
AlarmNumber AlarmsManager::getNextEmptyAlarm(){
  Alarm testAlarm;
  for(int i = 0; i < 8; i++){
    testAlarm = getAlarm((AlarmNumber)i);
    if(testAlarm.getBinaryRepresentation() == 0) {
      return (AlarmNumber)i;
    }
  }
  return (AlarmNumber)0;
}
void AlarmsManager::clearAlarm(AlarmNumber alarmNumber){
  EEPROM.write(51+alarmNumber +2, 0);
 EEPROM.write(51+alarmNumber +0, 0);
EEPROM.write(51+alarmNumber +1, 0); 
}
