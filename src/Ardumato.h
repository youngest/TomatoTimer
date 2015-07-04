#ifndef _ARDUMATO_H
#define _ARDUMATO_H

#include <Arduino.h>
#include "Symbol.h"
#include "Tomato.h"
#include "TomatoDisplay.h"

class Ardumato: public TomatoDisplay {
public:
  Ardumato(int outputEnable = 11, int serialPin = 6, int latchPin = 7, int clockPin = 10, int buttonPin = 4);
  void loop();
  bool debounceButton();
  void displaySeconds(uint16_t);

private:
  volatile uint16_t seconds;
  int outputEnable;
  int serialPin;
  int latchPin;
  int clockPin;
  int buttonPin;
  int clockDriver;
  int clockInterrupt;

  Tomato *tomato;

  void displayTime();
  void setupClock();
  void setupInputs();
  void setupShiftRegisters();
  void writeSymbolInSegment(uint16_t symbol, uint16_t segment);
};

static Ardumato *ardumato;
#define StartArdumato() ardumato = new Ardumato()
#define LoopArdumato() ardumato->loop()

#endif
