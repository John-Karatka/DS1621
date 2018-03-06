/*
 * DS1621 - library for DS1621 digital thermometer
 * This library is intended to be used with Aruino Wire library functions
 *
 * Version 1.0
 * Last updated - 5/9/17
 * John Karatka
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Please send any questions or concerns to
 * john.karatka@gmail.com
 *
 ************************************************************************
 *
 * Wiring diagram for digital thermometer DS1621
 *
 *         ----
 *  1 SDA-|    |-VDD 8
 *  2 SCL-|    |-A0  7
 *  3 TOU-|    |-A1  6
 *  4 GND-|    |-A2  5
 *         ----
 */

#ifndef DS1621_H
#define DS1621_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class TempSense {
private:
	int address;
	int configSettings;
	signed int temperature;

	void checkConvert();
	void updateTemp();
	void updateConfig();

public:
	TempSense(int TempSenseAddress);
	signed int getTempF();
	signed int getTempC();
	void setTrigger(signed int tempTrigger);
	void setReset(signed int tempReset);
	int getConfig();
};

#endif
