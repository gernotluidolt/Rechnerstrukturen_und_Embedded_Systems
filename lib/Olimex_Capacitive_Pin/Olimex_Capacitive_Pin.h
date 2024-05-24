#ifndef	_CAPACITIVE_PIN_H
#define	_CAPACITIVE_PIN_H

#include <Arduino.h>

class Olimex_Capacitive_Pin
{
public:
	Olimex_Capacitive_Pin (int _Pin);
	uint8_t Read();
private:
	int Pin;
};
#endif