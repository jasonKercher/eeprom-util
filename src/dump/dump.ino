#ifdef LIBTEST
#include "libtest.h"
#else
#include <Arduino.h>
#include <EEPROM.h>
#endif

void setup()
{
	Serial.begin(9600);
	unsigned long val = 0;
	for (unsigned i = 0; i < EEPROM.length(); i += sizeof(val)) {
		EEPROM.get(i, val);
		Serial.printf("%lu\n", val);
	}
}

void loop()
{
	delay(1000);
}
