/* 
  microbit_Screen.h - LED Screen library for micro:bit
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

#ifndef microbit_Screen_h
#define microbit_Screen_h

#include <Arduino.h>

const uint8_t max_cols PROGMEM = 9;
const uint8_t max_rows PROGMEM = 3;
const uint8_t colCount PROGMEM = 5;
const uint8_t rowCount PROGMEM = 5;
const uint8_t cols[max_cols] PROGMEM = {3, 4, 10, 23, 24, 25, 9, 7, 6};
const uint8_t rows[max_rows] PROGMEM = {26, 27, 28};

typedef struct TPoint {
  uint8_t x;
  uint8_t y;
} LED_POINT;

const LED_POINT LED_POS[rowCount][colCount] PROGMEM =
{
  {{0, 0}, {3, 1}, {1, 0}, {4, 1}, {2, 0}},
  {{3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}},
  {{1, 1}, {8, 0}, {2, 1}, {8, 2}, {0, 1}},
  {{7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}},
  {{2, 2}, {6, 1}, {0, 2}, {5, 1}, {1, 2}}
};

const uint8_t LED_FONT[96][colCount] PROGMEM =
{
  /* 0x20 - 0x2F */
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (Space)
  {0x00, 0x17, 0x00, 0x00, 0x00}, // !
  {0x00, 0x03, 0x00, 0x03, 0x00}, // "
  {0x0A, 0x1F, 0x0A, 0x1F, 0x0A}, // #
  {0x0A, 0x17, 0x15, 0x1D, 0x0A}, // $
  {0x13, 0x09, 0x04, 0x12, 0x19}, // %
  {0x0A, 0x15, 0x15, 0x0A, 0x10}, // &
  {0x00, 0x03, 0x00, 0x00, 0x00}, // '
  {0x00, 0x0E, 0x11, 0x00, 0x00}, // (
  {0x00, 0x11, 0x0E, 0x00, 0x00}, // )
  {0x00, 0x0A, 0x04, 0x0A, 0x00}, // *
  {0x00, 0x04, 0x0E, 0x04, 0x00}, // +
  {0x00, 0x10, 0x08, 0x00, 0x00}, // ,
  {0x00, 0x04, 0x04, 0x04, 0x00}, // -
  {0x00, 0x08, 0x00, 0x00, 0x00}, // .
  {0x10, 0x08, 0x04, 0x02, 0x01}, // /
  /* 0x30 - 0x3F */
  {0x00, 0x00, 0x00, 0x00, 0x00}, // 0
  {0x00, 0x12, 0x1F, 0x10, 0x00}, // 1
  {0x19, 0x15, 0x15, 0x12, 0x00}, // 2
  {0x09, 0x11, 0x15, 0x0B, 0x00}, // 3
  {0x0C, 0x0A, 0x09, 0x1F, 0x08}, // 4
  {0x17, 0x15, 0x15, 0x15, 0x09}, // 5
  {0x08, 0x14, 0x16, 0x15, 0x08}, // 6
  {0x11, 0x09, 0x05, 0x03, 0x01}, // 7
  {0x0A, 0x15, 0x15, 0x15, 0x0A}, // 8
  {0x02, 0x15, 0x0D, 0x05, 0x02}, // 9
  {0x00, 0x0A, 0x00, 0x00, 0x00}, // :
  {0x00, 0x10, 0x0A, 0x00, 0x00}, // ;
  {0x00, 0x04, 0x0A, 0x11, 0x00}, // <
  {0x00, 0x0A, 0x0A, 0x0A, 0x00}, // =
  {0x00, 0x11, 0x0A, 0x04, 0x00}, // >
  {0x02, 0x01, 0x15, 0x05, 0x02}, // ?
  /* 0x40 - 0x4F */
  {0x0E, 0x11, 0x15, 0x09, 0x0E}, // @
  {0x1E, 0x05, 0x05, 0x1E, 0x00}, // A
  {0x1F, 0x15, 0x15, 0x0A, 0x00}, // B
  {0x0E, 0x11, 0x11, 0x11, 0x00}, // C
  {0x1F, 0x11, 0x11, 0x0E, 0x00}, // D
  {0x1F, 0x15, 0x15, 0x11, 0x00}, // E
  {0x1F, 0x05, 0x05, 0x01, 0x00}, // F
  {0x0E, 0x11, 0x11, 0x15, 0x0C}, // G
  {0x1F, 0x04, 0x04, 0x1F, 0x00}, // H
  {0x11, 0x1F, 0x11, 0x00, 0x00}, // I
  {0x09, 0x11, 0x11, 0x0F, 0x01}, // J
  {0x1F, 0x04, 0x0A, 0x11, 0x00}, // K
  {0x1F, 0x10, 0x10, 0x10, 0x00}, // L
  {0x1F, 0x02, 0x04, 0x02, 0x1F}, // M
  {0x1F, 0x02, 0x04, 0x08, 0x1F}, // N
  {0x0E, 0x11, 0x11, 0x0E, 0x00}, // O
  /* 0x50 - 0x5F */
  {0x1F, 0x05, 0x05, 0x02, 0x00}, // P
  {0x06, 0x09, 0x19, 0x16, 0x00}, // Q
  {0x1F, 0x05, 0x05, 0x0A, 0x10}, // R
  {0x12, 0x15, 0x15, 0x09, 0x00}, // S
  {0x01, 0x01, 0x1F, 0x01, 0x01}, // T
  {0x0F, 0x10, 0x10, 0x0F, 0x00}, // U
  {0x07, 0x08, 0x10, 0x08, 0x07}, // V
  {0x1F, 0x08, 0x04, 0x08, 0x1F}, // W
  {0x1B, 0x04, 0x04, 0x1B, 0x00}, // X
  {0x01, 0x02, 0x1C, 0x02, 0x01}, // Y
  {0x19, 0x15, 0x13, 0x11, 0x00}, // Z
  {0x00, 0x1F, 0x11, 0x11, 0x00}, // [
  {0x01, 0x02, 0x04, 0x08, 0x10}, // (Backslash)
  {0x00, 0x11, 0x11, 0x1F, 0x00}, // ]
  {0x00, 0x02, 0x01, 0x02, 0x00}, // ^
  {0x10, 0x10, 0x10, 0x10, 0x10}, // _
  /* 0x60 - 0x6F */
  {0x00, 0x01, 0x02, 0x00, 0x00}, // `
  {0x0C, 0x12, 0x12, 0x1E, 0x10}, // a
  {0x1F, 0x14, 0x14, 0x08, 0x00}, // b
  {0x0C, 0x12, 0x12, 0x12, 0x00}, // c
  {0x08, 0x14, 0x14, 0x1F, 0x00}, // d
  {0x0E, 0x15, 0x15, 0x12, 0x00}, // e
  {0x04, 0x1E, 0x05, 0x01, 0x00}, // f
  {0x02, 0x15, 0x15, 0x0F, 0x00}, // g
  {0x1F, 0x04, 0x04, 0x18, 0x00}, // h
  {0x00, 0x1D, 0x00, 0x00, 0x00}, // i
  {0x00, 0x10, 0x10, 0x0D, 0x00}, // j
  {0x1F, 0x04, 0x0A, 0x10, 0x00}, // k
  {0x00, 0x0F, 0x10, 0x10, 0x00}, // l
  {0x1E, 0x02, 0x04, 0x02, 0x1E}, // m
  {0x1E, 0x02, 0x02, 0x1C, 0x00}, // n
  {0x0C, 0x12, 0x12, 0x0C, 0x00}, // o
  /* 0x70 - 0x7F */
  {0x1E, 0x0A, 0x0A, 0x04, 0x00}, // p
  {0x04, 0x0A, 0x0A, 0x1E, 0x00}, // q
  {0x1C, 0x02, 0x02, 0x02, 0x00}, // r
  {0x10, 0x14, 0x0A, 0x02, 0x00}, // s
  {0x00, 0x0F, 0x14, 0x14, 0x10}, // t
  {0x0E, 0x10, 0x10, 0x1E, 0x10}, // u
  {0x06, 0x08, 0x10, 0x08, 0x06}, // v
  {0x1E, 0x10, 0x08, 0x10, 0x1E}, // w
  {0x12, 0x0C, 0x0C, 0x12, 0x00}, // x
  {0x12, 0x14, 0x08, 0x04, 0x02}, // y
  {0x12, 0x1A, 0x16, 0x12, 0x00}, // z
  {0x00, 0x04, 0x1F, 0x11, 0x00}, // {
  {0x00, 0x1F, 0x00, 0x00, 0x00}, // |
  {0x11, 0x1F, 0x04, 0x00, 0x00}, // }
  {0x00, 0x04, 0x04, 0x08, 0x08}, // ~
  {0x00, 0x00, 0x00, 0x00, 0x00}  // (Del)
};

enum class IconNames {
  Heart = 0, 
  SmallHeart = 1,
  Yes = 2,
  No = 3,
  Happy = 4,
  Sad = 5,
  Confused = 6,
  Angry = 7,
  Asleep = 8,
  Surprised = 9,
  Silly = 10,
  Fabulous = 11,
  Meh = 12,
  TShirt = 13,
  Rollerskate = 14,
  Duck = 15,
  House = 16,
  Tortoise = 17,
  Butterfly = 18,
  StickFigure = 19,
  Ghost = 20,
  Sword = 21,
  Giraffe = 22,
  Skull = 23,
  Umbrella = 24,
  Snake = 25,
  Rabbit = 26,
  Cow = 27,
  QuarterNote = 28,
  EigthNote = 29,
  Pitchfork = 30,
  Target = 31,
  Triangle = 32,
  LeftTriangle = 33,
  Chessboard = 34,
  Diamond = 35,
  SmallDiamond = 36,
  Square = 37,
  SmallSquare = 38,
  Scissors = 39
};

const uint8_t LED_ICON[40][colCount] PROGMEM =
{
  {0x06, 0x0F, 0x1E, 0x0F, 0x06}, // Heart       
  {0x00, 0x06, 0x0C, 0x06, 0x00}, // SmallHeart  
  {0x08, 0x10, 0x08, 0x04, 0x02}, // Yes         
  {0x11, 0x0A, 0x04, 0x0A, 0x11}, // No          
  {0x08, 0x12, 0x10, 0x12, 0x08}, // Happy       
  {0x10, 0x0A, 0x08, 0x0A, 0x10}, // Sad         
  {0x10, 0x0A, 0x10, 0x0A, 0x10}, // Confused    
  {0x19, 0x0A, 0x18, 0x0A, 0x19}, // Angry       
  {0x02, 0x0A, 0x08, 0x0A, 0x02}, // Asleep      
  {0x00, 0x09, 0x14, 0x09, 0x00}, // Surprised   
  {0x05, 0x04, 0x04, 0x1C, 0x1D}, // Silly       
  {0x03, 0x1B, 0x11, 0x1B, 0x03}, // Fabulous    
  {0x01, 0x11, 0x08, 0x05, 0x01}, // Meh         
  {0x03, 0x1F, 0x1E, 0x1F, 0x03}, // TShirt      
  {0x0C, 0x1C, 0x0C, 0x1F, 0x0F}, // Rollerskate 
  {0x02, 0x0F, 0x0F, 0x0C, 0x04}, // Duck        
  {0x04, 0x1E, 0x0F, 0x1E, 0x04}, // House       
  {0x04, 0x0E, 0x06, 0x0E, 0x04}, // Tortoise    
  {0x1B, 0x1B, 0x0E, 0x1B, 0x1B}, // Butterfly   
  {0x12, 0x0A, 0x07, 0x0A, 0x12}, // StickFigure 
  {0x1E, 0x0D, 0x1F, 0x0D, 0x1E}, // Ghost       
  {0x00, 0x08, 0x1F, 0x08, 0x00}, // Sword       
  {0x01, 0x1F, 0x08, 0x18, 0x00}, // Giraffe     
  {0x06, 0x1D, 0x1F, 0x1D, 0x06}, // Skull       
  {0x1A, 0x13, 0x1F, 0x03, 0x02}, // Umbrella    
  {0x03, 0x0F, 0x08, 0x0E, 0x02}, // Snake       
  {0x1F, 0x1C, 0x17, 0x1C, 0x00}, // Rabbit      
  {0x07, 0x0C, 0x1C, 0x0C, 0x07}, // Cow         
  {0x18, 0x18, 0x1F, 0x00, 0x00}, // QuarterNote 
  {0x18, 0x18, 0x1F, 0x02, 0x04}, // EigthNote   
  {0x07, 0x04, 0x1F, 0x04, 0x07}, // Pitchfork   
  {0x04, 0x0E, 0x1B, 0x0E, 0x04}, // Target      
  {0x08, 0x0C, 0x0A, 0x0C, 0x08}, // Triangle    
  {0x1F, 0x12, 0x14, 0x18, 0x10}, // LeftTriangle
  {0x0A, 0x15, 0x0A, 0x15, 0x0A}, // Chessboard  
  {0x04, 0x0A, 0x11, 0x0A, 0x04}, // Diamond     
  {0x00, 0x04, 0x0A, 0x04, 0x00}, // SmallDiamond
  {0x1F, 0x11, 0x11, 0x11, 0x1F}, // Square      
  {0x00, 0x0E, 0x0A, 0x0E, 0x00}, // SmallSquare 
  {0x1B, 0x1B, 0x04, 0x0A, 0x11}, // Scissors    
};

const uint8_t LED_ARROW[8][colCount] PROGMEM =
{
  {0x04, 0x02, 0x1F, 0x02, 0x04}, // 0       
  {0x10, 0x08, 0x05, 0x03, 0x07}, // 1  
  {0x04, 0x04, 0x15, 0x0E, 0x04}, // 2         
  {0x01, 0x02, 0x14, 0x18, 0x1C}, // 3          
  {0x04, 0x08, 0x1F, 0x08, 0x04}, // 4
  {0x1C, 0x18, 0x14, 0x02, 0x01}, // 5
  {0x04, 0x0E, 0x15, 0x04, 0x04}, // 6
  {0x07, 0x03, 0x05, 0x08, 0x10}, // 7
};

class microbit_Screen {
private:
  bool screenArr[colCount][rowCount];
  void pset(const uint8_t x, const uint8_t y, const uint8_t mode);
  void showData(const uint8_t *DataArray);
public:
  microbit_Screen();
  void begin();
  void clearScreen();
  void plot(const uint8_t x, const uint8_t y);
  void unplot(const uint8_t x, const uint8_t y);
  void toggle(const uint8_t x, const uint8_t y);
  bool point(const uint8_t x, const uint8_t y);
  void showString(const String str);
  void showNumber(const int value);
  void showIcon(const IconNames icon);
  void showArrow(const uint8_t direction);
};

extern microbit_Screen SCREEN;

#endif
