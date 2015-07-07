#include "Tomato.h"
#include "TomatoAlarm.h"
#include "TomatoDisplay.h"

Tomato::Tomato(TomatoAlarm *alarm, TomatoDisplay *display, uint16_t ticksPerSecond)
{
  this->onBreak = false;
  this->breaksTaken = 0;
  this->clock = 0;
  this->clockSeconds = TOMATO_TIME;
  this->ticking = false;
  this->alarm = alarm;
  this->display = display;
  this->ticksPerSecond = ticksPerSecond;

  this->fireAlarm();
  this->updateDisplay();
}

void Tomato::reset()
{
  if (this->clockSeconds == 0) {
    this->resetTimer();
  }

  this->ticking = !this->ticking;
  this->updateDisplay();
}

void Tomato::resetTimer()
{
  this->onBreak = !this->onBreak;

  if (this->onBreak)
    this->takeABreak();
  else
    this->clockSeconds = TOMATO_TIME;
}

void Tomato::takeABreak()
{
  this->breaksTaken = (this->breaksTaken + 1) % 4;
  this->clockSeconds = this->breaksTaken ? BREAK_TIME : LONG_BREAK_TIME;
}

void Tomato::tick()
{
  if (this->ticking) {
    this->clock += 1;

    if (this->clock == this->ticksPerSecond) {
      this->decrementSeconds();
    }
  }
}

void Tomato::decrementSeconds()
{
  this->clockSeconds -= 1;
  this->ticking = this->clockSeconds > 0;
  this->updateDisplay();

  this->clock = 0;
}

void Tomato::fireAlarm()
{
  if (this->alarm) this->alarm->fireAlarm();
}

void Tomato::updateDisplay()
{
  if (this->display) this->display->displaySeconds(this->clockSeconds);
}
