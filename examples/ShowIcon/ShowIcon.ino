#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();
}

void loop() {
  SCREEN.showIcon(IconNames::Yes);  
  SCREEN.showIcon(IconNames::No);  
}
