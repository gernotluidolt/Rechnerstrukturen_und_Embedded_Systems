#ifndef	_TCN75_H
#define	_TCN75_H

#include <Arduino.h>
#include <Wire.h>

class Olimex_TCN75
{
public:
	Olimex_TCN75 (int _Address);
	int RawData ();
	float Temperature ();
private:
	int Address;
};

#endif
