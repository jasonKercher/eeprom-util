/** VERSION 205 **/
#include "fake_arduino.h"

#include <unistd.h>

static unsigned _pin_state[PIN_COUNT];
static unsigned _pin_mode[PIN_COUNT];

unsigned long millis()
{
        return 50;
}

int digitalRead(unsigned pin)
{
	return HIGH;
}

void digitalWrite(unsigned pin, unsigned state)
{
        if (pin > PIN_COUNT) {
                return;
        }
        _pin_state[pin] = state;
}

void pinMode(unsigned pin, unsigned mode)
{
        if (pin > PIN_COUNT) {
                return;
        }
        _pin_mode[pin] = mode;
}

void delay(unsigned delay_time)
{
        usleep(1000 * delay_time);
}


