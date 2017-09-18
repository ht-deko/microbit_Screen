#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();
}

void loop() {
  for (int i = 0; i < 8; i++)
    SCREEN.showArrow(i);
}
