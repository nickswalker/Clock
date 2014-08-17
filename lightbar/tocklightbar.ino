#include <IRremote.h>
#include "color_constants.h"

//#define DEBUG
#define REDPIN 6
#define GREENPIN 5
#define BLUEPIN 9

#define REDINPIN A0
#define GREENINPIN A1
#define BLUEINPIN A2

#define IRDIODEPIN 11
#define MICROSECONDSINSECOND 1000000

IRrecv irrecv(IRDIODEPIN);
decode_results results; // This will store our IR received codes
uint32_t irCode;

boolean stripIsOn;
uint32_t IRCode; 

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}
boolean isOn = false;
void loop() {

  if (irrecv.decode(&results))
  {
    uint16_t resultCode = (results.value & 0xFFFF);
    //decode caps out at 32bits
    //break the bytes out of this
    IRCode = (results.value & 0xFFFFFFF);
    Serial.println(IRCode,HEX);
    irrecv.resume(); // Receive the next value
    if(isOn){
      setColor(BLACK);
      isOn = false;
    }
    else{
      setColor(COOLWHITE);
      isOn = true;
    }
  }
}

//Execute series of fades with given speeds. Does size-1 fades
//In C, array parameters are passed by reference. Because of this, we only have a pointer to the first element, not the size. We need to pass it manually.
void runSequenceOfFades(RGB colors[], float speeds[], size_t size){
 for( int i = 0; i < size-1; i++){
  fadeBetweenColors(colors[i], colors[i+1],speeds[i]);
 }
  
}

//Blocking function that fades colors.
void fadeBetweenColors(RGB initialColor, RGB targetColor, float seconds){
  long loopDelayInMicroseconds = (seconds * MICROSECONDSINSECOND)/256;
  #ifdef DEBUG
  Serial.println(loopDelayInMicroseconds);
  Serial.println(loopDelayInMicroseconds/256);
  #endif
  float rFadeIncrement = (float)(targetColor.r - initialColor.r)/255;
  float gFadeIncrement = (float)(targetColor.g - initialColor.g)/255;
  float bFadeIncrement = (float)(targetColor.b - initialColor.b)/255; 
  
  //For debugging
  //Note how we need to cast to an int (uint8_t will not work). Not entirely sure why.
  //Serial.println("RGB Increments:");Serial.print(rFadeIncrement);Serial.print(" ");Serial.print(gFadeIncrement);Serial.print(" ");Serial.print(bFadeIncrement);Serial.println(" ");
  
  byte tempR, tempG, tempB;
  
  //We get at most 255 discrete steps because analogWrite has limited resolution
  //This means, in the extreme case, we step each value by one per iteration
  //There is no use in stepping in smaller increments as analogWrite is not capable of outputing with any more granularity
  //In the situation of the smallest possible delta, 1, the loop still executes 256 times, eventually adding 1 in the last interation
  for(int i=0; i<=255; i++){
     tempR = i*rFadeIncrement + initialColor.r;
     tempG = i*gFadeIncrement + initialColor.g;
     tempB = i*bFadeIncrement + initialColor.b;
     setColor(tempR,tempG,tempB);
     delayMicroseconds(loopDelayInMicroseconds);
  }
}

//Sets the state for the color pins
void setColor (byte r, byte g, byte b){
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b); 
  
  #ifdef DEBUG
  Serial.print(r);Serial.print(" ");Serial.print(g);Serial.print(" ");Serial.print(b);Serial.println(" ");
  #endif
}

//With the relative brightnesses of the LEDS in mind, remap full white to the calibrated WHITE constant.
//Pretty accurately predicts mixes calibrated by eye.
//Unfortunately, the brightness curve of the LEDs is not linear, so simple mapping will not work.
void perceptualSetColor (byte r, byte g, byte b){
  byte perceptualR = map(r, 0, 255, 0, (int)WHITE.r);
  byte perceptualG = map(g, 0, 255, 0, (int)WHITE.g);
  byte perceptualB = map(b, 0, 255, 0, (int)WHITE.b);
  setColor(perceptualR,perceptualG,perceptualB);
  
  //Heads up: Serial.print slows the loop way down. Won't reflect accurate timing
  #ifdef DEBUG
  Serial.print(perceptualR);Serial.print(" ");Serial.print(perceptualG);Serial.print(" ");Serial.print(perceptualB);Serial.println(" ");
  #endif
}

void setColor (RGB color){
  setColor((uint8_t)color.r,(uint8_t)color.g,(uint8_t)color.b);
}

void setColorFromAnalogIn(){
  byte r = map(analogRead(REDINPIN),  0, 1023, 0, 255);
  byte g = map(analogRead(GREENINPIN),0, 1023, 0, 255);
  byte b = map(analogRead(BLUEINPIN), 0, 1023, 0, 255);
  setColor(r,g,b);
}
