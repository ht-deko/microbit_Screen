#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();      // initialize LED screen
}

void loop() {
  SCREEN.plot(2, 2);   // turn the LED (2,2) on
  delay(1000);         // wait for a second
  SCREEN.unplot(2, 2); // turn the LED (2,2) off
  delay(1000);         // wait for a second
}
