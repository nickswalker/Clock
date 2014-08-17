#ifndef definitionsH
#define definitionsH

#define SPEAKERPIN 2
#define BUTTONPIN 5
#define STRIPPIN 9
#define LEDPIN 13
#define PHOTORESISTORPIN A0
#define PIEZOPIN A1
#define IRLEDPIN 10

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
  TESTCONNECTION =255      
} Command;

typedef enum{
  ALARM1 = 1,
  ALARM2 = 2,
  ALARM3 = 3,
  ALARM4 = 4,
  ALARM5 = 5,
  ALARM6 = 6,
  ALARM7 = 7
}  AlarmNumber;

typedef enum {
  DISPLAYTWENTYFOURHOURTIME,
  BLINKCOLON,
  LOUDERALARM,
  AUTOBRIGHTNESS,
  BRIGHTNESS
} Option;
typedef enum WeekBits{
  SUNDAY = 1 << 1,
  MONDAY = 1 << 2,
  TUESDAY = 1 << 3,
  WEDNESDAY = 1 << 4,
  THURSDAY = 1 << 5,
  FRIDAY = 1 << 6,
  SATURDAY = 1 << 7    
};

typedef struct{
  unsigned char activeAndRepeatSchedule;
  unsigned char hour;
  unsigned char minute;
} alarm_t;
#endif
