/** VERSION 205 **/
#include "fake_dmm.h"

bool is_mon(const unsigned char* s)
{
        /* return true if this is MON
         * request
         */
        return (s[0] == 0x8E &&
                s[1] == 0x9B &&
                s[2] == 0xA9);
}

void FakeDMM::write_pun()
{
        /* translates to PUN=18508
         */

        _in_buf[_in_head++] = 0x0;
        _in_buf[_in_head++] = 0xFB;
        _in_buf[_in_head++] = 0xB4;
        _in_buf[_in_head++] = 0xF2;
        _in_buf[_in_head++] = 0xA5;
        _in_buf[_in_head++] = 0xB4;
        _in_buf[_in_head++] = 0xFA;
}


int FakeDMM::available()
{
        if (_in_head - _in_tail) {
                _has_data = true;
                return (unsigned char) (_in_head - _in_tail);
        }

        if (_has_data) {
                _has_data = false;
        }

        return 0;
}

size_t FakeDMM::write(uint8_t b)
{
        /* If we haven't read 4 bytes yet */
        if (_out_head < 3) {
                _out_buf[_out_head++] = b;
                return 1;
        }

        /* shift all bytes */
        int i = 0;
        for (; i < FAKE_DMM_BUFSIZE - 1; ++i) {
                _out_buf[i] = _out_buf[i+1];
        }
        _out_buf[FAKE_DMM_BUFSIZE - 1] = b;

        /* Check for MON */
        if (is_mon(_out_buf)) {
                write_pun();
        }

        return 1;
}

size_t FakeDMM::write(const uint8_t *buffer, size_t size)
{
        unsigned i = 0;
        for (; i < size; ++i) {
                write (buffer[i]);
        }
        return 0;
}

size_t FakeDMM::print(const char* s) 
{
        for (; *s; ++s) {
                write(*s);
        }
        return 0;
}
size_t FakeDMM::println(const char* s)
{
        print(s);
        write('\n');
        return 0;
}
