/*-------------------------------------------------------------------------
  Arduino library for controlling a Light Sensor.

  Olimex_Light_Sensor (int _Pin) - initializes the class and sets which pin is used for the light sensor
  int Read () - returns the value of the light sensor (from 0 to 1023)
  float ReadPercentage () - returns the value of the light sensor as a percentage
  -------------------------------------------------------------------------*/

#include "Olimex_Light_Sensor.h"

Olimex_Light_Sensor::Olimex_Light_Sensor (int _Pin)
{
	Pin = _Pin;
	pinMode (Pin, INPUT_PULLUP);
}

int Olimex_Light_Sensor::Read ()
{
	return analogRead(Pin);
}

float Olimex_Light_Sensor::ReadPercentage ()
{
	return Read() * 100.0/1023.0;
}
