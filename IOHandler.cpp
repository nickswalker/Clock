#include "IOHandler.h"
#include "Settings.h"
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

#define STRIPPIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, STRIPPIN, NEO_GRB + NEO_KHZ800);
Adafruit_7segment matrix = Adafruit_7segment();

void IOHandler::init(){
  //I2C address
  
  strip.show(); // Initialize all pixels to 'off'
  strip.begin();
  matrix.begin(0x70);
  matrix.setBrightness(Settings::brightness());
  Serial.println("IOHandler setup complete");
}

void IOHandler::displayTime(byte hour, byte minute, byte second){
  bool pmDot = false;
  bool colon = false;
  if( Settings::displayTwelveHourTime() ){
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
  
  if( Settings::blinkColon() && second % 2 == 0 ) colon = true;
  writeDotsToMatrix(colon, pmDot);
  matrix.writeDisplay();
  //Serial.println(time);
}
void IOHandler::alarmBuzz(){
  tone(2000, 13);
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
   Settings::setBrightness(value);
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
uint32_t IOHandler::wheel(byte wheelPos) {
  if(wheelPos < 85) {
   return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  } else if(wheelPos < 170) {
   wheelPos -= 85;
   return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  } else {
   wheelPos -= 170;
   return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
}
