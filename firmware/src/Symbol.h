#ifndef _TOMATO_SYMBOL_H
#define _TOMATO_SYMBOL_H

#include <stdint.h>

const uint16_t SEG_A = 1024;
const uint16_t SEG_B = 64;
const uint16_t SEG_C = 16;
const uint16_t SEG_D = 16384;
const uint16_t SEG_E = 32768;
const uint16_t SEG_F = 2048;
const uint16_t SEG_G = 8;
const uint16_t SEG_DP = 8192;
const uint16_t DIGIT1 = 512;
const uint16_t DIGIT2 = 4096;
const uint16_t DIGIT3 = 32;
const uint16_t DIGIT4 = 4;
const uint16_t COLON_ENABLE = 0;
const uint16_t COLON = 128;
const uint16_t CLEAR = 0x1226;

const uint16_t DIGIT[] = {
  DIGIT2 | DIGIT3 | DIGIT4,
  DIGIT1 | DIGIT3 | DIGIT4,
  DIGIT1 | DIGIT2 | DIGIT4,
  DIGIT1 | DIGIT2 | DIGIT3
};

const uint16_t SYMBOL[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_B | SEG_C,
  SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,
  SEG_B | SEG_C | SEG_F | SEG_G,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_F | SEG_G
};

#endif
