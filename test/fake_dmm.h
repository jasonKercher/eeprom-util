/** VERSION 205 **/
#ifndef FAKE_DMM_H
#define FAKE_DMM_H

#include "fake_serial.h"

#define FAKE_DMM_BUFSIZE 3

/* Not honest for one second up here */
class FakeDMM : public FakeSerial {
private:
        unsigned char _out_head = 0;
        //unsigned char _out_tail = 0;
        unsigned char _out_buf[FAKE_DMM_BUFSIZE];

        void write_pun();
public:
        FakeDMM() : FakeSerial() {}
        FakeDMM(const char* in_name, const char* out_name) : FakeSerial(in_name, out_name) {}

	int available() override;

	size_t write(uint8_t b) override;
	size_t write(const uint8_t *buffer, size_t size) override;
        size_t print(const char*) override;
        size_t println(const char*) override;
};

#endif /* FAKE_DMM_H */
