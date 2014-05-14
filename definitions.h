#ifndef definitionsH
#define definitionsH

#define SPEAKERPIN 2
#define BUTTONPIN 5
#define STRIPPIN 9
#define LEDPIN 13
#define PHOTORESISTORPIN A0
#define PIEZOPIN A1
#define IRLEDPIN 0

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
  ALARM7 = 7,
  ALARM8 = 8,
}  AlarmNumber;

typedef enum {
  DISPLAYTWENTYFOURHOURTIME,
  BLINKCOLON,
  LOUDERALARM,
  AUTOBRIGHTNESS,
  BRIGHTNESS
} Option;

#endif
