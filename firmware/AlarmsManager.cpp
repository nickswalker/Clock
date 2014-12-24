#include "AlarmsManager.h"
#include "AlarmT.h"
#include "Time.h"
#include "Settings.h"
#include "BitManipulation.h"
#include <EEPROM.h>

#define MINUTEINDEX 0
#define HOURINDEX 1
#define REPEATINDEX 2

//MINUTE HOUR REPEAT
//BYTE0  BYTE1 BYTE2

void AlarmsManager::setAlarm(AlarmNumber alarmNumber, AlarmT alarm){
    EEPROM.write(Settings::getAlarmMinuteAddress(alarmNumber), alarm.getTriggerMinute());
    EEPROM.write(Settings::getAlarmHourAddress(alarmNumber), alarm.getTriggerHour());
    EEPROM.write(Settings::getAlarmRepeatAddress(alarmNumber), alarm.getSchedule());
}

AlarmNumber AlarmsManager::getNextEmptyAlarm(){
    for(int i = 0; i < 8; i++){
        AlarmT testAlarm = AlarmT((AlarmNumber)i);
        if(testAlarm.getIntRepresentation() == 0) {
            return (AlarmNumber)i;
        }
    }
    return (AlarmNumber)0;
}

boolean AlarmsManager::checkIfTimeTriggersAnyAlarm(uint8_t hour, uint8_t minute){
    for(int i = 0; i < 8; i++){
        AlarmT testAlarm = AlarmT((AlarmNumber)i);
        if(testAlarm.getTriggerHour() == hour && testAlarm.getTriggerMinute() == minute ) {
            if(testAlarm.isOn() && testAlarm.isActiveOnDay((timeDayOfWeek_t)weekday())){
                return true;
            }
        }
    }
    return false;
}

void AlarmsManager::clearAlarm(AlarmNumber alarmNumber){
    EEPROM.write(Settings::getAlarmMinuteAddress(alarmNumber), 0);
    EEPROM.write(Settings::getAlarmHourAddress(alarmNumber), 0);
    EEPROM.write(Settings::getAlarmRepeatAddress(alarmNumber), 0);
}

AlarmT AlarmsManager::getAlarm(AlarmNumber alarmNumber){
    return AlarmT(EEPROM.read(Settings::getAlarmRepeatAddress(alarmNumber)),
          EEPROM.read(Settings::getAlarmHourAddress(alarmNumber)),
          EEPROM.read(Settings::getAlarmMinuteAddress(alarmNumber))
          );
}
