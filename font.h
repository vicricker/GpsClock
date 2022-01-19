#ifndef FONT_H
#define FONT_H
#include <stdint.h>
#include <avr/pgmspace.h>

#define D_NW 0
#define D_HORIZ 1
#define D_NE 2
#define D_VERT 3
#define D_T_LEFT 4
#define D_T_RIGHT 5
#define D_SW 6
#define D_SE 7
#define SPACE ' '

const uint8_t NWW[] PROGMEM = {
  0b00000,
  0b00000,
  0b00000,
  0b00111,
  0b01111,
  0b01111,
  0b01110,
  0b01110
};
const uint8_t HORIZ[] PROGMEM = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000
};
const uint8_t NE[] PROGMEM = {
  0b00000,
  0b00000,
  0b00000,
  0b11100,
  0b11110,
  0b11110,
  0b01110,
  0b01110
};
const uint8_t VERT[] PROGMEM = {
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

const uint8_t T_RIGHT[] PROGMEM = {
  0b01110,
  0b01110,
  0b01110,
  0b01111,
  0b01111,
  0b01111,
  0b01110,
  0b01110
};

const uint8_t T_LEFT[] PROGMEM = {
  0b01110,
  0b01110,
  0b01110,
  0b11110,
  0b11110,
  0b11110,
  0b01110,
  0b01110
};

const uint8_t SW[] PROGMEM = {
  0b01110,
  0b01110,
  0b01110,
  0b01111,
  0b01111,
  0b00111,
  0b00000,
  0b00000
};

const uint8_t SX[] PROGMEM = {
  0b01110,
  0b01110,
  0b01110,
  0b11110,
  0b11110,
  0b11100,
  0b00000,
  0b00000
};


const uint8_t digit[][9] PROGMEM = {
  { //0
    D_NW, D_HORIZ, D_NE,
    D_VERT, SPACE, D_VERT,
    D_SW, D_HORIZ, D_SE

  },
  { // 1
    SPACE, D_NE, SPACE,
    SPACE, D_VERT, SPACE,
    SPACE, D_SW, SPACE,

  },
  { // 2
    D_NW, D_HORIZ, D_NE,
    D_NW, D_HORIZ, D_SE,
    D_SW, D_HORIZ, D_SE,

  },
  { // 3
    D_NW, D_HORIZ, D_NE,
    SPACE, D_HORIZ, D_T_LEFT,
    D_SW, D_HORIZ, D_SE

  },
  { // 4
    D_NW, SPACE, D_NE,
    D_SW, D_HORIZ, D_T_LEFT,
    SPACE, SPACE, D_SW

  },
  { // 5
    D_NW, D_HORIZ, D_NE,
    D_SW, D_HORIZ, D_NE,
    D_SW, D_HORIZ, D_SE

  },
  { // 6
    D_NW, D_HORIZ, D_NE,
    D_T_RIGHT, D_HORIZ, D_NE,
    D_SW, D_HORIZ, D_SE

  },
  { // 7
    D_NW, D_HORIZ, D_NE,
    SPACE, SPACE, D_VERT,
    SPACE, SPACE, D_SW

  },
  { // 8
    D_NW, D_HORIZ, D_NE,
    D_T_RIGHT, D_HORIZ, D_T_LEFT,
    D_SW, D_HORIZ, D_SE

  },
  { // 9
    D_NW, D_HORIZ, D_NE,
    D_SW, D_HORIZ, D_T_LEFT,
    SPACE, SPACE, D_SW

  }
};

#endif
