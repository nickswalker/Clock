#include "IOHandler.h"
#include "Settings.h"
#include "pin_definitions.h"
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, STRIPPIN, NEO_GRB + NEO_KHZ800);
Adafruit_7segment matrix = Adafruit_7segment();

void IOHandler::init(){
  pinMode(BUTTONPIN, INPUT);
  strip.show(); // Initialize all pixels to 'off'
  strip.begin();
  matrix.begin(0x70);
  matrix.setBrightness(Settings::getByte(brightness));
  Serial.println("IOHandler setup complete");
}

/* = Time Display
--------------------------------------------------------------*/

typedef enum DisplayDotsProperties{
  COLON = 1,
  UPPERLEFTDOT = 2,
  LOWERLEFTDOT = 3,
  UPPERRIGHTDOT = 4
        
};

void IOHandler::displayTime(byte hour, byte minute, byte second){
  bool pmDot = false;
  bool colon = true;
 
  if( Settings::getBool(displayTwelveHourTime) ){
    if(hour>=13){
      hour -= 12;
      pmDot = true;
    }
  }
  if( Settings::getBool(blinkColon) && second % 2 ) colon = true;
  
  matrix.clear();
  matrix.writeDigitNum(1,hour%10);
  matrix.writeDigitNum(3,0);
  matrix.writeDigitNum(4,minute%10);
  if(hour >= 10) matrix.writeDigitNum(0,hour/10);
  if (minute >= 10) matrix.writeDigitNum(3,minute/10);
  
  byte dotsBitmask = 0;
  dotsBitmask |= colon << COLON;
  dotsBitmask |= pmDot << UPPERLEFTDOT;
  matrix.writeDigitRaw(2, dotsBitmask);
  
  matrix.writeDisplay();

}

void IOHandler::setBrightness(byte value){
   matrix.setBrightness((int)value);
}

/* = Snooze Button
--------------------------------------------------------------*/
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

boolean IOHandler::checkIfSnoozeButtonWasPressed(){
  int reading = digitalRead(BUTTONPIN);
  boolean buttonWasPressed = false;
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == HIGH) {
        buttonWasPressed = true;
      }
      
    }
  }
  lastButtonState = reading;
  return buttonWasPressed;
}
void IOHandler::setAlarmState(boolean state){
  this->alarmIsOn = state;
  if(state){
    alarmBuzz(); 
  }
  else{
    noTone(SPEAKERPIN);
  }
}
boolean IOHandler::getAlarmState(){
  return this->alarmIsOn;
}
void IOHandler::alarmBuzz(){
  if(Settings::getBool(louderAlarm)) tone(SPEAKERPIN, 2000, 1000);
  else tone(SPEAKERPIN, 100);
   
}


/* = Built in Lights
--------------------------------------------------------------*/
void IOHandler::setLightColor(byte r, byte g, byte b, bool animated){
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

