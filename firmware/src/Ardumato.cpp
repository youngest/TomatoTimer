#include "Ardumato.h"
#include <avr/interrupt.h>
#include <avr/io.h>

const int DEBOUNCE_DELAY = 50;
static volatile int count = 0;
static volatile bool tick = false;

ISR(TIMER1_OVF_vect)
{
  count++;

  if (count == 100) {
    tick = true;
    count = 0;
  }

  TCNT1 = -625;
  TIFR1 = 0x00;
}

Ardumato::Ardumato(int outputEnable, int serialPin, int latchPin, int clockPin, int buttonPin, int buzzerPin)
{
  this->outputEnable = outputEnable;
  this->serialPin = serialPin;
  this->latchPin = latchPin;
  this->clockPin = clockPin;
  this->buttonPin = buttonPin;
  this->buzzerPin = buzzerPin;
  this->alarmTriggered = false;
  this->tomato = new Tomato(this, this, 1);

  this->setupClock();
  this->setupInputs();
  this->setupShiftRegisters();
}

void Ardumato::setupClock()
{
  TCCR1B = 0x00;  // Disable Timer1
  TCNT1 = -625;   // Set Timer1 Count to overflow after 625 ticks
  TIFR1 = 0x00;   // Clear Timer1 Interrupt flags
  TIMSK1 = 0x01;  // Enable Timer1 Overflow Interrupt
  TCCR1A = 0x00;  // Timer1 Control Reg A, normal mode
  TCCR1B = 0x04;  //Timer1 Control Reg B: Timer Prescaler set to 256
}

void Ardumato::setupInputs()
{
  pinMode(this->buttonPin, INPUT);
  pinMode(this->buzzerPin, OUTPUT);
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
  this->playAlarm();
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

void Ardumato::fireAlarm()
{
  this->alarmTriggered = true;
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

void Ardumato::playAlarm()
{
  static int alarmCycle = 3;
  static long nextAlarmTime = 0;

  if (this->alarmTriggered) {
    if (alarmCycle > 0) {
      if (millis() > nextAlarmTime) {
        alarmCycle -= 1;
        nextAlarmTime = millis() + 1000;
        tone(this->buzzerPin, 1024, 500);
      }
    } else {
      alarmCycle = 3;
      nextAlarmTime = 0;
      this->alarmTriggered = false;
    }
  }
}
