/** VERSION 205 **/
#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#define LOW     0
#define HIGH    1

#define LED_BUILTIN 0

#define OUTPUT 0
#define INPUT 1

#define PIN_COUNT 2

void setup();
void loop();

unsigned long millis();
int digitalRead(unsigned);
void digitalWrite(unsigned, unsigned);
void pinMode(unsigned, unsigned);
void delay(unsigned delay_time);

#endif /* FAKE_ARDUINO_H */
