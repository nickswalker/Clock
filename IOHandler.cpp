#include "IOHandler.h"
#include "Settings.h"
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

#define STRIPPIN 10
#define SNOOZEBUTTONPIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, STRIPPIN, NEO_GRB + NEO_KHZ800);
Adafruit_7segment matrix = Adafruit_7segment();

bool lastSnoozeButtonState = false;

void IOHandler::init(){
  pinMode(SNOOZEBUTTONPIN, INPUT);
  strip.show(); // Initialize all pixels to 'off'
  strip.begin();
  matrix.begin(0x70);
  matrix.setBrightness(Settings::getByte(brightness));
  Serial.println("IOHandler setup complete");
}

void IOHandler::displayTime(byte hour, byte minute, byte second){
  bool pmDot = false;
  bool colon = true;
  if( Settings::getBool(displayTwelveHourTime) ){
    if(hour>=13){
      hour -= 12;
      pmDot = true;
    }
  }
  matrix.clear();
  matrix.writeDigitNum(1,hour%10);
  matrix.writeDigitNum(3,0);
  matrix.writeDigitNum(4,minute%10);
  if(hour >= 10) matrix.writeDigitNum(0,hour/10);
  if (minute >= 10) matrix.writeDigitNum(3,minute/10);
  
  if( Settings::getBool(blinkColon) && second % 2 == 1 ) colon = false;
  writeDotsToMatrix(colon, pmDot);
  matrix.writeDisplay();
  //Serial.println(time);
}
void IOHandler::alarmBuzz(){
  //This is incredibly loud. Use the other line during testing
  //tone(2, 2000, 1000);
  
  tone(2, 100, 1000);
}
int lastReadingTime = 0;
bool IOHandler::readSnoozeButton(){
  
  bool currentReading = digitalRead(SNOOZEBUTTONPIN);
  if(currentReading == true){
    
    if( (millis() - lastReadingTime) > 1000 ){
    Serial.println((millis() - lastReadingTime));
    lastReadingTime = millis();
    return true;
    }
  }
  
  return false;
  
}
void IOHandler::writeDotsToMatrix(bool colon, bool pmDot)  {
  byte bitmask;
  if (colon && pmDot) bitmask = 6;
  else if (colon && !pmDot) bitmask = 2;
  else if (!colon && pmDot) bitmask = 4;
  matrix.writeDigitRaw(2, bitmask);
}
void IOHandler::setBrightness(byte value){
   matrix.setBrightness((int)value);
   Settings::set(brightness, (byte)value);
}
void IOHandler::rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void IOHandler::setLightColor(byte r, byte g, byte b, bool animated){
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,r,g,b);
  }
  strip.show();
}

