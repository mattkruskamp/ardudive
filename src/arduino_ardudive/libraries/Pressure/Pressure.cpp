/*
  	Pressure.cpp - Library for getting the pressure
	from a pressure sensor. Aids in getting depth
	information as well.
*/

#include "Arduino.h"
#include "Pressure.h"

Pressure::Pressure(int pin, int maxPressure)
{
	_pin = pin;
	_maxPressure = maxPressure;
}

int Pressure::getRawPressure()
{
	return analogRead(_pin);
}

int Pressure::getDepth()
{
	int reading, pounds, feet;
	
	// calculate the depth
	reading = getRawPressure();
	pounds = _maxPressure * reading / 1024;
	feet = pounds * 33 / 14.7;
	
	// normalize for consistancy
	if(feet > 5)
	{
		feet = 5;
	}
	
	return feet;
}