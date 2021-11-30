/** VERSION 205 **/
#ifndef FAKE_SERIAL_H
#define FAKE_SERIAL_H

#include <iostream>
#include <fstream>
#include <climits>
#include <stdarg.h>

#include "fake_stream.h"

#ifndef SERIAL_7E1
#define SERIAL_7E1 0
#endif

class FakeSerial : public FakeStream {

protected:
        std::ofstream _out_file_stream;
        std::ostream* _out_stream;
        std::ifstream _in_file_stream;
        std::istream* _in_stream;

        unsigned char _in_buf[UCHAR_MAX + 1];
        unsigned char _in_head = 0;
        unsigned char _in_tail = 0;

        bool _has_data = false;


public:
        FakeSerial();
        FakeSerial(const char* in_name, const char* out_name);
        
        /* Stream overrides */
	virtual int available() override;
	int read() override;
	int peek() override;

        void begin(size_t);
        void begin(size_t, int);

        /* Print.h overrides */
	void flush();

	size_t write(uint8_t b) override;
        size_t write(const char*) override;
	virtual size_t write(const uint8_t *buffer, size_t size);

        size_t print(const char*) override;
        size_t println(const char*) override;
        size_t printf(const char*, ...);
};

typedef FakeSerial HardwareSerial;
typedef FakeSerial usb_serial_class;

#endif /* FAKE_SERIAL_H */
