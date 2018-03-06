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

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "DS1621.h"
#include <Wire.h>

#define StartConvertion 0xEE
#define StopConvertion 0x22
#define GetTemperature 0xAA
#define TemperatureHigh 0xA1
#define TemperatureLow 0xA2
#define Config 0xAC
#define ReadCounter 0xA8
#define ReadSlope 0xA9

//! Constructor
TempSense::TempSense(int TempSenseAddress) {
	address = TempSenseAddress;
	Wire.begin();
}

/*
 * @brief  Checks if chip is done temperature conversion
 * @retval None
 */
void TempSense::checkConvert() {
	while (configSettings < 128) {
		updateConfig();
	}
}

/*
 * @brief  Gets temperature value from chip
 * @retval Tempurature
 */
void TempSense::updateTemp() {

	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(StartConvertion);
	#else
		Wire.send(StartConvertion);
	#endif

	Wire.endTransmission();
	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(StopConvertion);
	#else
		Wire.send(StopConversion);
	#endif

	Wire.endTransmission();
	checkConvert();
	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(GetTemperature);
	#else
		Wire.send(GetTemperature);
	#endif

	Wire.endTransmission(false);
	Wire.requestFrom(address, 2);
	#if ARDUINO >= 100
		temperature = Wire.read();
		Wire.read();
	#else	
		temperature = Wire.receive();
		Wire.receive();
	#endif
}

/*
 * @brief  Gets configuration from chip
 * @retval None
 */
void TempSense::updateConfig() {
	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(Config);
	#else
		Wire.send(Config);
	#endif
	
	Wire.endTransmission(false);
	Wire.requestFrom(address, 1);
	#if ARDUINO >= 100
		configSettings = Wire.read();
	#else
		configSettings = Wire.receive();
	#endif
}

/*
 * @brief  Retrieves Temperature in Fahrenheit
 * @retval Tempurature as Fahrenheit
 */
signed int TempSense::getTempF() {
	updateTemp();
	return((temperature * 9 / 5) + 32);
}

/*
 * @brief  Retrieves Temperature in Celsius
 * @retval Tempurature as Celsius
 */
signed int TempSense::getTempC() {
	updateTemp();
	return(temperature);
}

/*
 * @brief  Sets output trigger
 * @param  tempTrigger: Trigger temperature value
 * @retval None
 */
void TempSense::setTrigger(signed int tempTrigger) {
	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(TemperatureHigh);
		Wire.write(tempTrigger);
		Wire.write(0);
	#else
		Wire.send(TemperatureHigh);
		Wire.send(tempTrigger);
		Wire.send(0);
	#endif
	
	Wire.endTransmission();
}

/*
 * @brief  Sets output reset
 * @param  tempReset: Reset temperature value
 * @retval None
 */
void TempSense::setReset(signed int tempReset) {
	Wire.beginTransmission(address);

	#if ARDUINO >= 100
		Wire.write(TemperatureLow);
		Wire.write(tempReset);
		Wire.write(0);
	#else
		Wire.send(TemperatureLow);
		Wire.send(tempReset);
		Wire.send(0);
	#endif
	
	Wire.endTransmission();
}

/*
 * @brief  Retrieves Configuration settings
 * @retval Configuration settings
 */
int TempSense::getConfig() {
	getConfig();
	return(configSettings);
}
