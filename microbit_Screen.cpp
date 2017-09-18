/*
  microbit_Screen.cpp - LED Screen library for micro:bit
  (Arduino Core for Nordic Semiconductor nRF5 based boards)
  Copyright (c) 2017 Hideaki Tominaga. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "microbit_Screen.h"

microbit_Screen::microbit_Screen() {
}

void microbit_Screen::begin() {
  for (int i = 0; i < max_cols; i++)
    pinMode(cols[i], OUTPUT);
  for (int i = 0; i < max_rows; i++)
    pinMode(rows[i], OUTPUT);
  clearScreen();
}

void microbit_Screen::clearScreen() {
  for (int i = 0; i < max_cols; i++)
    digitalWrite(cols[i], HIGH);
  for (int i = 0; i < max_rows; i++)
    digitalWrite(rows[i], LOW);
  for (uint8_t l = 0; l < rowCount; l++) {
    for (uint8_t i = 0; i < colCount; i++) {
      screenArr[i][l] = false;
    }
  }
}

void microbit_Screen::pset(const uint8_t x, const uint8_t y, const uint8_t mode) {
  LED_POINT position = LED_POS[y][x];
  digitalWrite(cols[position.x], !mode);
  digitalWrite(rows[position.y], mode);
  screenArr[x][y] = (mode == HIGH) ;
}

void microbit_Screen::plot(const uint8_t x, const uint8_t y) {
  pset(x, y, HIGH);
}

void microbit_Screen::unplot(const uint8_t x, const uint8_t y) {
  pset(x, y, LOW);
}

void microbit_Screen::toggle(const uint8_t x, const uint8_t y) {
  screenArr[x][y] = !screenArr[x][y];
  pset(x, y, screenArr[x][y]);
}

bool microbit_Screen::point(const uint8_t x, const uint8_t y) {
  return (screenArr[x][y]);
}

void microbit_Screen::showData(const uint8_t column, const uint8_t colData) {
  uint8_t data = colData;
  for (uint8_t y = 0; y < rowCount; y++) {
    if (data & 1) {
      LED_POINT position = LED_POS[y][column];
      digitalWrite(cols[position.x], LOW );
      digitalWrite(rows[position.y], HIGH);
      delay(1);
      digitalWrite(cols[position.x], HIGH);
      digitalWrite(rows[position.y], LOW );
    } else {
      delay(1);
    }
    data = data >> 1;
  }  
}

void microbit_Screen::showString(const String str) {
  clearScreen();

  String dStr;
  if (str.length() == 0)
    dStr = " ";
  else if (str.length() == 1)
    dStr = str;
  else
    dStr = " " + str + " ";
  bool isSingleChar = (dStr.length() == 1);
  uint8_t* strBuf = new uint8_t[dStr.length() * colCount + colCount - 1];

  int idx = 0;
  for (int c = 0; c < dStr.length(); c++) {
    int charidx = dStr.charAt(c);
    if ((charidx < 0x20) || (charidx > 0x7f))
      charidx = 0x00;
    else
      charidx = charidx - 0x20;
    for (uint8_t x = 0; x < colCount; x++) {
      strBuf[idx] = LED_FONT[charidx][x];
      idx++;
    }
    if (c < dStr.length() - 1) {
      strBuf[idx] = 0x00;
      idx++;
    }
  }

  idx = 0;
  do {
    unsigned long tick = millis();
    do {
      for (uint8_t x = 0; x < colCount; x++) {
        showData(x, strBuf[x + idx]);
      }
    } while ((millis() - tick) < 150); 
    idx++;
  } while ((idx < dStr.length() * colCount + colCount) && !isSingleChar);

  delete[] strBuf;
}

void microbit_Screen::showNumber(const int value) {
  String dStr = String(value, DEC);
  showString(dStr);
}

void microbit_Screen::showIcon(const IconNames icon) {
  unsigned long tick = millis();
  do {
    for (uint8_t x = 0; x < colCount; x++) {
      showData(x, LED_ICON[(int)icon][x]);
    }
  } while ((millis() - tick) < 750);  
}

void microbit_Screen::showArrow(const uint8_t direction) {
  uint8_t d = direction % 8;
  unsigned long tick = millis();
  do {
    for (uint8_t x = 0; x < colCount; x++) {
      showData(x, LED_ARROW[d][x]);
    }
  } while ((millis() - tick) < 750);  
}

microbit_Screen SCREEN;
