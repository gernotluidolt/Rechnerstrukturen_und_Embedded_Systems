/*-------------------------------------------------------------------------
  Arduino library for controlling a Buzzer.

  Olimex_Joystick (int PinX, int PinY) - initializes the class (to be used with the Arduino pins which detect the axis change in the joystick)
  Olimex_Joystick (int PinX, int PinY, int PinBut);
  int X_Raw ();
  int Y_Raw ();
  float X ();
  float Y ();
  bool But ();
  -------------------------------------------------------------------------*/

#include "Olimex_Joystick.h"

Olimex_Joystick::Olimex_Joystick (int PinX, int PinY)
{
	X_Axis = PinX;
	Y_Axis = PinY;

	Button_on_digital_pin = false;
	DDRE = DDRE & 0xFB;	// hardcoded button on pin PE2
	pinMode (X_Axis, INPUT_PULLUP); // Joystick X axis
	pinMode (Y_Axis, INPUT_PULLUP); // Joystick Y axis
}

Olimex_Joystick::Olimex_Joystick (int PinX, int PinY, int PinBut)
{
	X_Axis = PinX;
	Y_Axis = PinY;
	B = PinBut;

	Button_on_digital_pin = true;
	pinMode (B, INPUT);
	pinMode (X_Axis, INPUT_PULLUP); // Joystick X axis
	pinMode (Y_Axis, INPUT_PULLUP); // Joystick Y axis
}

int Olimex_Joystick::X_Raw ()
{
	return analogRead(X_Axis);
}

int Olimex_Joystick::Y_Raw ()
{
	return analogRead(Y_Axis);
}

float Olimex_Joystick::X ()
{
	return analogRead(X_Axis) * 100.0 / 1023.0;
}

float Olimex_Joystick::Y ()
{
	return analogRead(Y_Axis) * 100.0 / 1023.0;
}

bool Olimex_Joystick::But ()
{
	if (Button_on_digital_pin)
		return digitalRead (B);
	else
		return PINE & 0x04;
}
