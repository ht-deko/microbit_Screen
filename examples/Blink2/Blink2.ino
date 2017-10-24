#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();      // initialize LED screen
}

void loop() {
  SCREEN.toggle(2, 2); // toggle the LED (2,2)
  delay(1000);         // wait for a second
}
