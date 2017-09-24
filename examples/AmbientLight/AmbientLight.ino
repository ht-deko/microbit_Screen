#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();  
}

void loop() {
  if (SCREEN.ambientLight() > 10) 
    SCREEN.showIcon(IconNames::Happy); // dazzling!
  else  
    SCREEN.showIcon(IconNames::Sad);
}
