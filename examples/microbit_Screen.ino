#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();
}

void loop() {
  SCREEN.showString("HELLO,WORLD.");  
  SCREEN.showString("micro:bit!");  
}
