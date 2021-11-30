/** VERSION 205 **/

#ifdef LIBTEST
#include "libtest.h"
#else
#include <Arduino.h>
#include <EEPROM.h>
#endif

void setup()
{
	Serial.begin(9600);
	const unsigned long val = 0;
	for (unsigned i = 0; i < EEPROM.length(); i += sizeof(val)) {
		EEPROM.put(i, val);
	}
}

void loop()
{
	delay(1000);
}
