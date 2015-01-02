#include "AlarmT.h"
#include "BitManipulation.h"
#include "Time.h"
#include "Settings.h"
#include <Arduino.h>

typedef enum {
    ON = 1 << 0 ,
    SUNDAY = 1 << 1,
    MONDAY = 1 << 2,
    TUESDAY = 1 << 3,
    WEDNESDAY = 1 << 4,
    THURSDAY = 1 << 5,
    FRIDAY = 1 << 6,
    SATURDAY = 1 << 7
} RepeatSchedule;

#define MINUTEINDEX 0
#define HOURINDEX 1
#define SCHEDULEINDEX 2

AlarmT::AlarmT(uint32_t packedAlarm){
    uint8_t bytes[4];
    BitManipulation::intToBytes(packedAlarm, bytes);
    init(bytes[SCHEDULEINDEX],bytes[HOURINDEX],bytes[MINUTEINDEX]);
}

AlarmT::AlarmT(uint8_t schedule, uint8_t hour, uint8_t minute){
    init(schedule, hour, minute);
}

void AlarmT::init(uint8_t schedule, uint8_t hour, uint8_t minute){
    this->binary.hour = hour;
    this->binary.minute = minute;
    this->binary.schedule = schedule;
}

boolean AlarmT::isOn(){
    return bitRead(this->binary.schedule, ON);
}

boolean AlarmT::isActiveOnDay(timeDayOfWeek_t day){
    return bitRead(this->binary.schedule, day);
}

void AlarmT::setOn(boolean value){
    uint8_t oldValue = this->binary.schedule;
    this->binary.schedule = bitWrite(oldValue, ON, value);
}

void AlarmT::setActiveOnDay(timeDayOfWeek_t day, boolean value){
    uint8_t oldValue = this->binary.schedule;
    this->binary.schedule = bitWrite(oldValue, (int)day, value);
}

uint8_t AlarmT::getTriggerHour(){
    return this->binary.hour; 
}

uint8_t AlarmT::getTriggerMinute(){
    return this->binary.minute; 
}

uint8_t AlarmT::getSchedule(){
    return this->binary.schedule; 
}

//Little Endian
//00000000 REPEAT HOUR MINUTE
//Byte3    Byte2  Byte1 Byte0
uint32_t AlarmT::getIntRepresentation(){
    return BitManipulation::separateBytesToInt(
            this->binary.minute,
            this->binary.hour,
            this->binary.schedule, 0);

}
