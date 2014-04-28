#ifndef definitionsH
#define definitionsH

#define DHT11PIN 2
#define SPEAKERPIN 2
#define PIRSENSORPIN 4
#define BUTTONPIN 5
#define STRIPPIN 9
#define LEDPIN 13
#define PHOTORESISTORPIN 14
#define IRLEDPIN 14

typedef enum Command{
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
};

typedef enum AlarmNumber{
  ALARM1 = 1,
  ALARM2 = 2,
  ALARM3 = 3,
  ALARM4 = 4,
  ALARM5 = 5,
  ALARM6 = 6,
  ALARM7 = 7,
  ALARM8 = 8,
};

typedef enum Option{
  DISPLAYTWENTYFOURHOURTIME,
  BLINKCOLON,
  LOUDERALARM,
  AUTOBRIGHTNESS,
  BRIGHTNESS
};

#endif
