/*
	Thermistor.h - Library for getting the temperature
	information from a thermistor.
*/
#ifndef Thermistor_h
#define Thermistor_h

#include "Arduino.h"

class Thermistor
{
	public:
    	Thermistor(int pin, float resistance, float c1,
			float c2, float c3);
		int getTemperature();
	private:
		int _pin;
		float _resistance;
		float _c1;
		float _c2;
		float _c3;
};

#endif