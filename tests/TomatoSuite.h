#include <cxxtest/TestSuite.h>
#include <Tomato.h>
#include <TomatoDisplay.h>

class TomatoSuite : public CxxTest::TestSuite, public TomatoDisplay
{
  uint16_t seconds;
  Tomato *tomato;

public:
  void setUp()
  {
    this->tomato = new Tomato(this);
  }

  void testInitialization()
  {
    TS_ASSERT_EQUALS(this->seconds, 20 * SECONDS_PER_MINUTE);
  }

  void testTickOnce()
  {
    this->tomato->tick();

    TS_ASSERT_EQUALS(this->seconds, 20 * SECONDS_PER_MINUTE);
  }

  void testCanTickOneSecond()
  {
    this->tickSeconds(1);

    TS_ASSERT_EQUALS(this->seconds, 20 * SECONDS_PER_MINUTE - 1);
  }

  void testCanTickToZero()
  {
    this->tickSeconds(20 * SECONDS_PER_MINUTE);

    TS_ASSERT_EQUALS(this->seconds, 0);
  }

  void testCannotTickPastZero()
  {
    this->tickSeconds(20 * SECONDS_PER_MINUTE + 1);

    TS_ASSERT_EQUALS(this->seconds, 0);
  }

  void tickSeconds(int seconds)
  {
    for (int i=0; i < seconds * TICKS_PER_SECOND; i++)
      this->tomato->tick();
  }

  void displaySeconds(uint16_t seconds)
  {
    this->seconds = seconds;
  }

};
