/*
  	Thermistor.cpp - Library for getting temperature
	information from a thermistor.
*/

#include "Arduino.h"
#include "math.h"
#include "Thermistor.h"

Thermistor::Thermistor(int pin, float resistance, float c1,
	float c2, float c3)
{
	_pin = pin;
	_resistance = resistance;
	_c1 = c1;
	_c2 = c2;
	_c3 = c3;
}

int Thermistor::getTemperature()
{
	int voltage;
	float logRt, rt, temp;
	
	// get the voltage
	voltage = analogRead(_pin);
	
	// calculate the resistance
	rt = _resistance * (1024.0 / (float)voltage - 1.0);
	logRt = log(rt);
	
	// get the temperature using Kelvin
	temp = (1.0 / (_c1 + _c2 * logRt + _c3 * logRt * logRt * logRt)) - 273.15;
	
	// convert to farenheight
	temp = (temp * 9.0) / 5.0 + 32.0;
	
	return (int)temp;
}