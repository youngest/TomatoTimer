#include <cxxtest/TestSuite.h>
#include <Tomato.h>
#include <TomatoAlarm.h>
#include <TomatoDisplay.h>

class TomatoSuite : public CxxTest::TestSuite, public TomatoAlarm, public TomatoDisplay
{
  bool alarmTriggered;
  uint16_t seconds;
  Tomato *tomato;

public:
  void setUp()
  {
    this->tomato = new Tomato(this, this);
  }

  void testInitialization()
  {
    TS_ASSERT_EQUALS(this->seconds, TOMATO_TIME);
  }

  void testAlarmTriggeredOnInitialization()
  {
    TS_ASSERT_EQUALS(this->alarmTriggered, true);
  }

  void testMustResetBeforeTicking()
  {
    this->tickSeconds(1);
    TS_ASSERT_EQUALS(this->seconds, TOMATO_TIME);

    this->resetAndTickSeconds(1);
    TS_ASSERT_EQUALS(this->seconds, TOMATO_TIME - 1);
  }

  void testCanTickOneSecond()
  {
    this->resetAndTickSeconds(1);

    TS_ASSERT_EQUALS(this->seconds, TOMATO_TIME - 1);
  }

  void testCanTickToZero()
  {
    this->resetAndTickSeconds(TOMATO_TIME);

    TS_ASSERT_EQUALS(this->seconds, 0);
  }

  void testCannotTickPastZero()
  {
    this->resetAndTickSeconds(TOMATO_TIME + 1);

    TS_ASSERT_EQUALS(this->seconds, 0);
  }

  void testAlarmFiredAtBeginningOfBreak()
  {
    this->clearAlarm();
    this->resetAndTickSeconds(TOMATO_TIME);

    TS_ASSERT_EQUALS(this->alarmTriggered, true);
  }

  void testResetAfterTomatoStartsBreak()
  {
    this->resetAndTickSeconds(TOMATO_TIME);
    this->reset();

    TS_ASSERT_EQUALS(this->seconds, BREAK_TIME);
  }

  void testResetAfterBreakStartsTomato()
  {
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->reset();

    TS_ASSERT_EQUALS(this->seconds, TOMATO_TIME);
  }

  void testResetAfterFourthTomatoStartsLongBreak()
  {
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->reset();

    TS_ASSERT_EQUALS(this->seconds, LONG_BREAK_TIME);
  }

  void testBreakAfterLongBreakIsStandardDuration()
  {
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->resetAndTickSeconds(LONG_BREAK_TIME);
    this->resetAndTickSeconds(TOMATO_TIME);
    this->reset();

    TS_ASSERT_EQUALS(this->seconds, BREAK_TIME);
  }

  void reset()
  {
    this->tomato->reset();
  }

  void tick()
  {
    this->tomato->tick();
  }

  void resetAndTickSeconds(int seconds)
  {
    this->reset();
    this->tickSeconds(seconds);
  }

  void tickSeconds(int seconds)
  {
    for (int i=0; i < seconds * TICKS_PER_SECOND; i++)
      this->tick();
  }

  void displaySeconds(uint16_t seconds)
  {
    this->seconds = seconds;
  }

  void fireAlarm()
  {
    this->alarmTriggered = true;
  }

  void clearAlarm()
  {
    this->alarmTriggered = false;
  }

};
