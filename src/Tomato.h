#ifndef _TOMATO_H
#define _TOMATO_H

#include <cstdlib>
#include "Symbol.h"
#include "TomatoDisplay.h"

#define SECONDS_PER_MINUTE 60
#define TICKS_PER_SECOND 490

class Tomato {
public:
  void tick();
  Tomato(TomatoDisplay *display = NULL, uint16_t ticksPerSecond = TICKS_PER_SECOND);

private:
  int OutputEnable;
  int SerialPin;
  int LatchPin;
  int ClockPin;
  int ClockDriver;
  int ClockInterrupt;

  volatile uint16_t clock;
  volatile uint16_t clockSeconds;
  uint16_t lastSecond;
  uint16_t startSecond;
  uint16_t ticksPerSecond;

  TomatoDisplay *display;

  void decrementSeconds();
  inline void updateDisplay();
};

#endif
