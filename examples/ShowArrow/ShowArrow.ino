#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();
}

void loop() {
  // CW
  for (int i = 0; i < 8; i++)
    SCREEN.showArrow((ArrowNames)i);
  // CCW
  SCREEN.showArrow(ArrowNames::North);
  SCREEN.showArrow(ArrowNames::NorthWest);
  SCREEN.showArrow(ArrowNames::West);
  SCREEN.showArrow(ArrowNames::SouthWest);
  SCREEN.showArrow(ArrowNames::South);
  SCREEN.showArrow(ArrowNames::SouthEast);
  SCREEN.showArrow(ArrowNames::East);
  SCREEN.showArrow(ArrowNames::NorthEast);
}
