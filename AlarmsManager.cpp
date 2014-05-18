#include "AlarmsManager.h"
#include "Alarm.h"
#include <EEPROM.h>

//Alarms start at byte 51
//MINUTE HOUR REPEAT
//BYTE0  BYTE1 BYTE2
uint32_t AlarmsManager::getAlarm(AlarmNumber alarmNumber){
  Alarm temp = Alarm( EEPROM.read(51+(alarmNumber*3) + 2 ), EEPROM.read(51+(alarmNumber*3) +1), EEPROM.read(51+(alarmNumber*3) +0) );
  return temp.getBinaryRepresentation();
  
}
void AlarmsManager::setAlarm(AlarmNumber alarmNumber, uint32_t alarmBinary){
      unsigned char byte0 = (alarmBinary >> 0);
      unsigned char byte1 = (alarmBinary >> 8);
      unsigned char byte2 = (alarmBinary >> 16);

  EEPROM.write(51+(alarmNumber*3) +0, byte0);
  EEPROM.write(51+(alarmNumber*3) +1, byte1); 
  EEPROM.write(51+(alarmNumber*3) +2, byte2);
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

boolean AlarmsManager::checkIfTimeTriggersAnyAlarm(uint8_t hour, uint8_t minute){
  Alarm testAlarm;
  uint32_t testAlarmBinary;
  for(int i = 0; i < 8; i++){
    testAlarmBinary = getAlarm((AlarmNumber)i);
    testAlarm = Alarm(testAlarmBinary);
    if(testAlarm.getTriggerHour() == hour && testAlarm.getTriggerMinute() == minute ) {
      return true;
    }
  }
  return false;
}

void AlarmsManager::clearAlarm(AlarmNumber alarmNumber){
  EEPROM.write(51+(alarmNumber*3) +2, 0);
 EEPROM.write(51+(alarmNumber*3) +0, 0);
EEPROM.write(51+(alarmNumber*3) +1, 0); 
}

