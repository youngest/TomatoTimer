#ifndef _TOMATO_H
#define _TOMATO_H

#include <Arduino.h>
#include "TomatoAlarm.h"
#include "TomatoDisplay.h"

#define SECONDS_PER_MINUTE 60
#define TICKS_PER_SECOND 490
#define BREAK_TIME 5 * SECONDS_PER_MINUTE
#define LONG_BREAK_TIME 20 * SECONDS_PER_MINUTE
#define TOMATO_TIME 20 * SECONDS_PER_MINUTE

class Tomato {
public:
  void reset();
  void tick();
  Tomato(TomatoAlarm *alarm = NULL, TomatoDisplay *display = NULL, uint16_t ticksPerSecond = TICKS_PER_SECOND);

private:
  volatile uint16_t clock;
  volatile uint16_t clockSeconds;
  uint16_t lastSecond;
  uint16_t startSecond;
  uint16_t ticksPerSecond;
  volatile uint8_t breaksTaken;
  volatile bool onBreak;
  volatile bool ticking;

  TomatoAlarm *alarm;
  TomatoDisplay *display;

  void decrementSeconds();
  void takeABreak();
  void resetTimer();
  inline void fireAlarm();
  inline void updateDisplay();
};

#endif
