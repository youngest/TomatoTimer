# TomatoTimer

This repository contains hardware specifications and software that together define a simple Pomodoro timer.

# Hardware

Under hardware/ you will find the hardware specifications:

### TomatoDisplaySMD.fzz

This Fritzing sketch defines a simple circuit that drives a 4 digit 7-segment display for the timer. The sketch is ready to be built on a breadboard or exported to Gerber files and fabricated.

#### *Revision A header pins*
The header labelled '1' on the board provides inputs to two shift registers that drive the display:

* Pin 1: VCC
* Pin 2: DS (serial in)
* Pin 3: GND
* Pin 4: SRCLK (storage register clock)
* Pin 5: SCLK (shift register clock)
* Pin 6: OE (output enable, active low)

### TomatoDisplaySMD_bom.html

This is the Bill of Materials exported from Fritzing, updated to include supplier part numbers.

# Firmware

Under firmware/ you will find the software that implements the timer logic and output.

### Tomato / TomatoAlarm / TomatoDisplay

Tomato is the primary class that defines the Tomato timer logic. TomatoAlarm and TomatoDisplay are interfaces that Tomato uses to communicate to a hardware implementation (i.e.: Ardumato). A suite of CxxTest unit tests are defined in tests/TomatoSuite.h. They can be run by executing `make test` from the firmware/ directory.

### Ardumato

Ardumato is a class that drives a Tomato instance with an Arduino Uno. It may work with other Arduino models, but none have been tested.
