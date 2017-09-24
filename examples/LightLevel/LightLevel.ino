#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();  
}

void loop() {
  if (SCREEN.lightLevel() > 10) 
    SCREEN.showIcon(IconNames::Happy);
  else  
    SCREEN.showIcon(IconNames::Sad);
}
