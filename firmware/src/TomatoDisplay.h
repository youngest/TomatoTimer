#ifndef _TOMATO_DISPLAY_H
#define _TOMATO_DISPLAY_H

#include <stdint.h>

class TomatoDisplay {
public:
  virtual void displaySeconds(uint16_t) = 0;
};

#endif
