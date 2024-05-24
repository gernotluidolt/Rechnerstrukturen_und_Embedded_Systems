/*-------------------------------------------------------------------------
  Arduino library for controlling a Capacitive Pin

	Olimex_Capacitive_Pin (int _Pin) - initializes the class and set tthe capacitive pin
	uint8_t Read() - reads the pin value (between 0 and 30)
  -------------------------------------------------------------------------*/

#include "Olimex_Capacitive_Pin.h"

Olimex_Capacitive_Pin::Olimex_Capacitive_Pin (int _Pin) 
{
	Pin = _Pin;
}

uint8_t Olimex_Capacitive_Pin::Read() {

  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;

  //  Here we translate the input pin number from the
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and we care about which bit of those registers.

  byte bitmask;

  port = portOutputRegister(digitalPinToPort(Pin));
  ddr = portModeRegister(digitalPinToPort(Pin));
  bitmask = digitalPinToBitMask(Pin);

  pin = portInputRegister(digitalPinToPort(Pin));

  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  delay(1);

  uint8_t SREG_old = SREG; //back up the AVR Status Register

  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();

  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long it takes for the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each reading of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 20;

  if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}
  else if (*pin & bitmask) { cycles = 17;}
  else if (*pin & bitmask) { cycles = 18;}
  else if (*pin & bitmask) { cycles = 19;}
  else if (*pin & bitmask) { cycles = 20;}
  else if (*pin & bitmask) { cycles = 21;}
  else if (*pin & bitmask) { cycles = 22;}
  else if (*pin & bitmask) { cycles = 23;}
  else if (*pin & bitmask) { cycles = 24;}
  else if (*pin & bitmask) { cycles = 25;}
  else if (*pin & bitmask) { cycles = 26;}
  else if (*pin & bitmask) { cycles = 27;}
  else if (*pin & bitmask) { cycles = 28;}
  else if (*pin & bitmask) { cycles = 29;}
  else if (*pin & bitmask) { cycles = 30;}

  // End of timing-critical section; turn interrupts back on if they were on before, or leave them off if they were off before
  SREG = SREG_old;

  //  Discharge the pin again by setting it to low and to output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}