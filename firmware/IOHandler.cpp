#include "IOHandler.h"
#include "Settings.h"
#include "definitions.h"
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

Adafruit_7segment matrix = Adafruit_7segment();

void IOHandler::init(){
  pinMode(BUTTONPIN, INPUT);
  pinMode(SPEAKERPIN, OUTPUT);
  matrix.begin(0x70);
  matrix.setBrightness(Settings::getByte(BRIGHTNESS));
  #ifdef DEBUG
    Serial.println("IOHandler setup complete");
  #endif
}

/* = Time Display
--------------------------------------------------------------*/

typedef enum{
    COLON = 1 << 1,
    UPPERLEFTDOT = 1 << 2,
    LOWERLEFTDOT = 1 << 3,
    UPPERRIGHTDOT = 1 << 4
} DisplayDotsProperties;

void IOHandler::displayTime(byte hour, byte minute, byte second){
    matrix.clear();
    char dotsBitmask = 0;
    dotsBitmask |= COLON;
    boolean evenSecond = (second % 2) == 1;
    if( Settings::getBool(BLINKCOLON) && evenSecond ){
        //Toggle the colon bit
        dotsBitmask ^= COLON;
    }
    if( !Settings::getBool(DISPLAYTWENTYFOURHOURTIME) ){
        if(hour >= 13){
            hour -= 12;
            dotsBitmask |= UPPERLEFTDOT;
        }
    }

    int rightHour = hour % 10;
    int leftHour = hour / 10;

    int rightMinute = minute % 10;
    int leftMinute = minute / 10;


    matrix.writeDigitNum(1, rightHour);
    matrix.writeDigitNum(3, 0);
    matrix.writeDigitNum(4, rightMinute);
    if(leftHour >= 1){
        matrix.writeDigitNum(0, leftHour);
    }
    matrix.writeDigitNum(3, minute / 10);
  
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
long debounceDelay = 1;    // the debounce time; increase if the output flickers

boolean IOHandler::checkIfSnoozeButtonWasPressed(){
  int reading = analogRead(PIEZOPIN);
  
  if (reading > 1003){
      reading = HIGH;
  }
  else{
      reading = LOW;
  }
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

/* = Alarm
--------------------------------------------------------------*/
void IOHandler::setAlarmState(boolean state){
    if(state){
      digitalWrite(SPEAKERPIN, HIGH);
    }
    else{
      digitalWrite(SPEAKERPIN, LOW);
     }
    this->alarmIsOn = state;

}

boolean IOHandler::getAlarmState(){
    return this->alarmIsOn;
}



