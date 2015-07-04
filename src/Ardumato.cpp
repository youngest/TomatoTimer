#include "Ardumato.h"
#include <avr/interrupt.h>
#include <avr/io.h>

const int DEBOUNCE_DELAY = 50;
static volatile int count = 0;
static volatile bool tick = false;

ISR(TIMER2_OVF_vect)
{
  count++;

  if (count == 999) {
    tick = true;
    count = 0;
  }

  TCNT2 = 130;
  TIFR2 = 0x00;
}

Ardumato::Ardumato(int outputEnable, int serialPin, int latchPin, int clockPin, int buttonPin)
{
  this->outputEnable = outputEnable;
  this->serialPin = serialPin;
  this->latchPin = latchPin;
  this->clockPin = clockPin;
  this->buttonPin = buttonPin;
  this->tomato = new Tomato(this, 1);

  this->setupClock();
  this->setupInputs();
  this->setupShiftRegisters();
}

void Ardumato::setupClock()
{
  //Setup Timer2 to fire every 1ms
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
}

void Ardumato::setupInputs()
{
  pinMode(this->buttonPin, INPUT);
}

void Ardumato::setupShiftRegisters()
{
  pinMode(this->outputEnable, OUTPUT);
  pinMode(this->serialPin, OUTPUT);
  pinMode(this->latchPin, OUTPUT);
  pinMode(this->clockPin, OUTPUT);

  digitalWrite(this->outputEnable, LOW);
}

void Ardumato::loop()
{
  if (this->debounceButton()) {
    this->tomato->reset();
  }

  if (tick) {
    tick = false;
    this->tomato->tick();
  }

  this->displayTime();
}

bool Ardumato::debounceButton()
{
  static int buttonState;
  static int lastButtonState = LOW;
  static long lastDebounceTime = 0;
  bool button = false;
  int reading = digitalRead(this->buttonPin);

  if (reading != lastButtonState)
    lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH)
        button = true;
    }
  }

  lastButtonState = reading;
  return button;
}

void Ardumato::displaySeconds(uint16_t seconds)
{
  this->seconds = seconds;
}

void Ardumato::displayTime()
{
  int minute = this->seconds / 60;
  int second = this->seconds % 60;
  int a = second % 10;
  int b = (second / 10) % 10;
  int c = minute % 10;
  int d = (minute / 10) % 10;

  this->writeSymbolInSegment(SYMBOL[d], DIGIT[0]);
  this->writeSymbolInSegment(SYMBOL[c], DIGIT[1]);
  this->writeSymbolInSegment(SYMBOL[b], DIGIT[2]);
  this->writeSymbolInSegment(SYMBOL[a], DIGIT[3]);
}

void Ardumato::writeSymbolInSegment(uint16_t symbol, uint16_t segment)
{
  uint16_t symbolWithColonAndDigit = segment | symbol | COLON;
  byte* output = (byte*)symbolWithColonAndDigit;
  digitalWrite(this->latchPin, LOW);
  shiftOut(this->serialPin, this->clockPin, MSBFIRST, (symbolWithColonAndDigit >> 8));
  shiftOut(this->serialPin, this->clockPin, MSBFIRST, symbolWithColonAndDigit);
  digitalWrite(this->latchPin, HIGH);

  delay(1);
}
