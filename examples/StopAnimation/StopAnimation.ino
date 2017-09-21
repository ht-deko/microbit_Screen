#include "microbit_Screen.h"

void setup() {
  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_A), onButtonPressed, CHANGE);
  
  SCREEN.begin();
  SCREEN.showString("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
}

void loop() {
  SCREEN.setBrightness(255);
  SCREEN.showIcon(IconNames::Heart);
  SCREEN.setBrightness(16);
  SCREEN.showIcon(IconNames::Heart);
}

void onButtonPressed() {
  SCREEN.stopAnimation();
}
