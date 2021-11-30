/** VERSION 205 **/
#ifndef FAKE_STREAM_H
#define FAKE_STREAM_H

#include <stdio.h>
#include <inttypes.h>

class FakeStream
{
private:
        int _dummy = 0;
public:
        FakeStream();
        
        /* Stream.h interface */
	virtual int available() = 0;
	virtual int read() = 0;
	virtual int peek() = 0;

        /* Print.h interface */
        virtual size_t print(const char*) = 0;
        virtual size_t println(const char*) = 0;
        virtual size_t printf(const char*, ...) = 0;
        virtual size_t write(uint8_t) = 0;
        virtual size_t write(const char*) = 0;
};

typedef FakeStream Stream;

#endif /* FAKE_STREAM_H */
