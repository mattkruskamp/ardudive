/*
	Pressure.h - Library for getting the pressure
	from a pressure sensor. Aids in getting depth
	information as well.
*/
#ifndef Pressure_h
#define Pressure_h

#include "Arduino.h"

class Pressure
{
	public:
    	Pressure(int pin, int maxPressure);
		int getRawPressure();
		int getDepth();
	private:
		int _pin;
		int _maxPressure;
};

#endif