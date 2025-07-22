#include <Wire.h>
#include <DS1621.h>

#define address 0	//chip address

TempSense tmp(address);

void setup() {
Wire.begin();
Serial.begin(115200);
}

void loop() {
signed int temperature = tmp.getTempF();

Serial.println(temperature);
delay(1000);
}
