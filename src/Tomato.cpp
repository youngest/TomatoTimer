#include "Tomato.h"
#include "TomatoDisplay.h"

Tomato::Tomato(TomatoDisplay *display, uint16_t ticksPerSecond)
{
  this->clock = 0;
  this->clockSeconds = 20 * SECONDS_PER_MINUTE;
  this->display = display;
  this->ticksPerSecond = ticksPerSecond;

  this->updateDisplay();
}

void Tomato::tick()
{
  this->clock += 1;

  if (this->clock == this->ticksPerSecond) {
    this->decrementSeconds();
  }
}

void Tomato::decrementSeconds()
{
  if (this->clockSeconds) {
    this->clockSeconds -= 1;
    this->updateDisplay();
  }

  this->clock = 0;
}

void Tomato::updateDisplay()
{
  if (this->display) this->display->displaySeconds(this->clockSeconds);
}
