/*
  microbit_Screen.cpp - LED Screen library for micro:bit
  (for "Arduino Core for Nordic Semiconductor nRF5 based boards")
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

/**
   pset() - private method
*/
void microbit_Screen::pset(const uint8_t x, const uint8_t y, const uint8_t mode) {
  if (!isEnabled)
    return;

  LED_POINT position = LED_POS[y][x];
  digitalWrite(cols[position.x], !mode);
  digitalWrite(rows[position.y], mode);
  screenArr[x][y] = (mode == HIGH) ;
}

/**
   showData() - private method
*/
void microbit_Screen::showData(const uint8_t *DataArray) {
  if (!isEnabled)
    return;

  uint32_t idx = 0;
  do {
    for (uint8_t x = 0; x < colCount; x++) {
      uint8_t data = DataArray[x];
      for (uint8_t y = 0; y < rowCount; y++) {
        if ((data & 1) && (idx < currentBrightness)) {
          LED_POINT position = LED_POS[y][x];
          digitalWrite(cols[position.x], LOW );
          digitalWrite(rows[position.y], HIGH);
          delayMicroseconds(5);
          digitalWrite(cols[position.x], HIGH);
          digitalWrite(rows[position.y], LOW );
        }
        data >>= 1;
      }
    }
    idx++;
  } while (idx < 256);
}

/**
   constructor
*/
microbit_Screen::microbit_Screen() {
}

/**
 * ambientLight()
 * LED as Sensor.
 */
uint32_t microbit_Screen::ambientLight() {
  int v = 0;
  for (int x = 0; x < 3; x++) {
    digitalWrite(cols[x], LOW);
    pinMode(cols[x], INPUT);
    v += analogRead(cols[x]);
    pinMode(cols[x], OUTPUT);
    digitalWrite(cols[x], HIGH);
  }
  // Serial.println(v);
  return max(darknessValue - v, 0);  
}

/**
   begin()
   Set it once in setup().
*/
void microbit_Screen::begin() {
  for (uint8_t i = 0; i < max_cols; i++)
    pinMode(cols[i], OUTPUT);
  for (uint8_t i = 0; i < max_rows; i++)
    pinMode(rows[i], OUTPUT);
  isEnabled = true;
  clearScreen();
}

/**
   brightness()
   https://makecode.microbit.org/reference/led/brightness
*/
uint8_t microbit_Screen::brightness() {
  return (currentBrightness);
}

/**
 * clearScreen()
 * https://makecode.microbit.org/reference/basic/clear-screen
 */
void microbit_Screen::clearScreen() {
  for (uint8_t i = 0; i < max_cols; i++)
    digitalWrite(cols[i], HIGH);
  for (uint8_t i = 0; i < max_rows; i++)
    digitalWrite(rows[i], LOW);
  for (uint8_t l = 0; l < rowCount; l++) {
    for (uint8_t i = 0; i < colCount; i++) {
      screenArr[i][l] = false;
    }
  }
  setBrightness(0xFF);
  isAnimated = true;
}

/**
   enable()
   https://makecode.microbit.org/reference/led/enable
*/
void microbit_Screen::enable(bool on) {
  isEnabled = on;
  if (!isEnabled)
    clearScreen();
}

/**
   plot()
   https://makecode.microbit.org/reference/led/plot
*/
void microbit_Screen::plot(const uint8_t x, const uint8_t y) {
  pset(x, y, HIGH);
}

/**
   plotBarGraph()
   https://makecode.microbit.org/reference/led/plot-bar-graph
*/
void microbit_Screen::plotBarGraph(const uint32_t value, const uint32_t high) {
  uint8_t LED_DATA[colCount] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint32_t dValue = value;
  uint32_t dHigh = high;
  if (dHigh < 15)
    dHigh = 15;
  if (dValue > dHigh)
    dValue = dHigh;

  uint8_t percentage = dValue * 100 / dHigh;
  uint8_t shiftBit = 5 - (percentage / 20);
  uint8_t remainder = (percentage % 20);
  uint8_t remainderBit = 1 << (shiftBit - 1);
  for (uint8_t i = 0; i < colCount; i++)
    LED_DATA[i] <<= shiftBit;
  if (remainder > 13) {
    LED_DATA[0] |= remainderBit;
    LED_DATA[4] |= remainderBit;
  }
  if (remainder > 6) {
    LED_DATA[1] |= remainderBit;
    LED_DATA[3] |= remainderBit;
  }
  LED_DATA[2] |= remainderBit;

  showData(LED_DATA);
}

/**
   plotBrightness()
   https://makecode.microbit.org/reference/led/plot-brightness
*/
void microbit_Screen::plotBrightness(const uint8_t x, const uint8_t y, const uint8_t brightness) {
  if (!isEnabled)
    return;

  uint32_t idx = 0;
  LED_POINT position = LED_POS[y][x];
  do {
    if (idx < brightness) {
      digitalWrite(cols[position.x], LOW);
      digitalWrite(rows[position.y], HIGH);
      delayMicroseconds(1);
      digitalWrite(cols[position.x], HIGH);
      digitalWrite(rows[position.y], LOW);
    }
    idx++;
  } while (idx < 256);
}

/**
   point()
   https://makecode.microbit.org/reference/led/point
*/
bool microbit_Screen::point(const uint8_t x, const uint8_t y) {
  return (screenArr[x][y]);
}

/**
   setBrightness()
   https://makecode.microbit.org/reference/led/set-brightness
*/
void microbit_Screen::setBrightness(const uint8_t value) {
  currentBrightness = value;
}

/**
   showArrow()
   https://makecode.microbit.org/reference/basic/show-arrow
*/
void microbit_Screen::showArrow(const ArrowNames direction, const uint32_t interval) {
  uint8_t d = (int)direction % 8;
  uint32_t tick = millis();
  do {
    showData(LED_ARROW[d]);
  } while ((millis() - tick) < interval);
}

/**
   showAnimation()
   https://makecode.microbit.org/reference/basic/show-animation
*/
void microbit_Screen::showAnimation(const String str, const uint32_t interval) {
  uint8_t numLineChar = (str.length() / rowCount);
  uint8_t numAnimation = (numLineChar + 1) / (colCount * 2);
  uint8_t charWidth = colCount * 2; 
  uint8_t* strBuf = new uint8_t[numAnimation * colCount]();

  for (uint32_t f = 0; f < numAnimation; f++) {
    for (int y = 0; y < rowCount; y++) {
      for (int x = 0; x < colCount; x++) {
        if (str.charAt((f * charWidth) + (y * numLineChar) + (x * 2)) == 0x23)
          bitWrite(strBuf[f * colCount + x], y, HIGH);
      }
    }
  }  
  
  for (uint32_t f = 0; f < numAnimation; f++) {
    uint32_t tick = millis();
    do {
      if (!isAnimated) {
        clearScreen();
        break;
      }
      showData(&strBuf[f * colCount]);
    } while ((millis() - tick) < interval);
  }

  delete[] strBuf;
}

/**
   showIcon()
   https://makecode.microbit.org/reference/basic/show-icon
*/
void microbit_Screen::showIcon(const IconNames icon, const uint32_t interval) {
  uint32_t tick = millis();
  do {
    showData(LED_ICON[(int)icon]);
  } while ((millis() - tick) < interval);
}

/**
   showLeds()
   https://makecode.microbit.org/reference/basic/show-leds
*/
void microbit_Screen::showLeds(const String str, const uint32_t interval) {
  uint8_t LED_DATA[colCount] = {0, 0, 0, 0, 0};

  for (int y = 0; y < rowCount; y++) {
    for (int x = 0; x < colCount; x++) {
      if (str.charAt((y * (colCount * 2 - 1) + (x * 2) )) == 0x23)
        bitWrite(LED_DATA[x], y, HIGH);
    }
  }

  uint32_t tick = millis();
  do {
    showData(LED_DATA);
  } while ((millis() - tick) < interval);
}

/**
   showNumber()
   https://makecode.microbit.org/reference/basic/show-number
*/
void microbit_Screen::showNumber(const int32_t value, const uint32_t interval) {
  String dStr = String(value, DEC);
  showString(dStr, interval);
}

/**
   showString()
   https://makecode.microbit.org/reference/basic/show-string
*/
void microbit_Screen::showString(const String text, const uint32_t interval) {
  clearScreen();

  String dStr;
  if (text.length() == 0)
    dStr = " ";
  else if (text.length() == 1)
    dStr = text;
  else
    dStr = " " + text + " ";
  bool isSingleChar = (dStr.length() == 1);
  uint32_t bufSize = dStr.length() * (colCount + 1) - 1;
  uint8_t* strBuf = new uint8_t[bufSize];

  uint32_t idx = 0;
  for (uint32_t c = 0; c < dStr.length(); c++) {
    uint32_t charidx = dStr.charAt(c);
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
    if (!isAnimated) {
      clearScreen();
      break;
    }
    uint32_t tick = millis();
    do {
      showData(&strBuf[idx]);
    } while ((millis() - tick) < interval);
    idx++;
  } while ((idx < (bufSize - colCount - 1)) && !isSingleChar);

  delete[] strBuf;
}

/**
   stopAnimation()
   https://makecode.microbit.org/reference/led/stop-animation
*/
void microbit_Screen::stopAnimation() {
  isAnimated = false;
}

/**
   toggle()
   https://makecode.microbit.org/reference/led/toggle
*/
void microbit_Screen::toggle(const uint8_t x, const uint8_t y) {
  screenArr[x][y] = !screenArr[x][y];
  pset(x, y, screenArr[x][y]);
}

/**
   unplot()
   https://makecode.microbit.org/reference/led/unplot
*/
void microbit_Screen::unplot(const uint8_t x, const uint8_t y) {
  pset(x, y, LOW);
}

microbit_Screen SCREEN;
