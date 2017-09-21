#include "microbit_Screen.h"

void setup() {
  SCREEN.begin();
}

void loop() {
  SCREEN.showAnimation((String)
    ". . # . . . # # # . . # # # ." + 
    ". # # . . . . . # . . . . # ." + 
    ". . # . . . . # . . . # # # ." + 
    ". . # . . . # . . . . . . # ." + 
    ". . # . . . # # # . . # # # ."
  );
}
