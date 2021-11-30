/** VERSION 205 **/
#ifndef LIBTEST_H
#define LIBTEST_H

#include <cstring>

#include "fake_arduino.h"
#include "fake_serial.h"
#include "fake_dmm.h"
#include "fake_eeprom.h"

/* These macros define input/output files for 
 * fake serial ports. To utilize terminal for
 * input/output there are special file names
 * available:
 *  - stdout
 *  - stdin
 *  - stderr
 */

#define LITERAL(s) #s

// debug port
#define SERIAL_IN       LITERAL(serial.in)
#define SERIAL_OUT      LITERAL(stderr)

// yas
#define SERIAL1_IN      LITERAL(serial1.in)
#define SERIAL1_OUT     LITERAL(stdout)

// dmm
#define SERIAL3_IN      LITERAL(serial3.in)
#define SERIAL3_OUT     LITERAL(serial3.out)

typedef FakeSerial HardwareSerial;

HardwareSerial  Serial (SERIAL_IN,  SERIAL_OUT);
HardwareSerial  Serial1(SERIAL1_IN, SERIAL1_OUT);
FakeDMM         Serial3(SERIAL3_IN, SERIAL3_OUT);

#endif /* LIBTEST_H */
