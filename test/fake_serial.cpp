/** VERSION 205 **/
#include "fake_serial.h"

#include <cstring>
#include <fstream>

#define LINE_ENDING_LF          1
#define LINE_ENDING_CR          2
#define LINE_ENDING_CRLF        3

std::istream& safegetline(std::istream& is, std::string& s, int& lineEnding)
{
        s.clear();
        std::istream::sentry se(is, true);
        std::streambuf* sb = is.rdbuf();

        for(;;)
        {
                int c = sb->sbumpc();
                switch (c)
                {
                case '\n':
                        lineEnding = LINE_ENDING_LF;
                        s += '\n';
                        return is;
                case '\r':
                        if(sb->sgetc() == '\n')
                        {
                                lineEnding = LINE_ENDING_CRLF;
                                s += "\r\n";
                                sb->sbumpc();
                        } else {
                                lineEnding = LINE_ENDING_CR;
                                s += '\r';
                        }

                        return is;
                case std::streambuf::traits_type::eof():
                        // Also handle the case when the last line has no line ending
                        if(s.empty()) {
                                is.setstate(std::ios::eofbit);
                        }
                        return is;
                default:
                        s += (char)c;
                }
        }
}


FakeSerial::FakeSerial()
{
        _in_stream = &std::cin;
        _out_stream = &std::cout;
}

FakeSerial::FakeSerial(const char* in_name, const char* out_name)
{
        if (in_name && !strcmp(in_name, "stdin")) {
                _in_stream = &std::cin;
        } else if (in_name) {
                _in_file_stream = std::ifstream(in_name);
                if (!_in_file_stream) {
                        std::cerr << "Failed to open " << in_name << " for reading\n";
                        exit(EXIT_FAILURE);
                }
                _in_stream = &_in_file_stream;
        }
        

        if (out_name && !strcmp(out_name, "stdout")) {
                _out_stream = &std::cout;
        } else if (out_name && !strcmp(out_name, "stderr")) {
                _out_stream = &std::cerr;
        } else if (out_name) {
                _out_file_stream = std::ofstream(out_name);
                if (!_out_file_stream) {
                        std::cerr << "Failed to open " << out_name << " for writing\n";
                        exit(EXIT_FAILURE);
                }
                _out_stream = &_out_file_stream;
        }

}

void FakeSerial::begin(size_t baud_rate) {}
void FakeSerial::begin(size_t baud_rate, int protocol) {}

/** STREAM **/
int FakeSerial::available()
{
        std::string input = "";
        //int line_ending = 0;

        /* As far as simulation goes, this `if` is wrong.
         * read should be attempted regardless of curent
         * buffer size.
         */
        if(_in_head - _in_tail) {
                _has_data = true;
                return (unsigned char) (_in_head - _in_tail);
        }

        if (_has_data) {
                _has_data = false;
                return 0;
        }

        char c = 0;
        if (!_in_stream->get(c)) {
                return 0;
        }
        
        _in_buf[_in_head++] = c;

        return input.length();
}

int FakeSerial::read()
{
        int ret = peek();
        ++_in_tail;
        return ret;
}

int FakeSerial::peek()
{
        if (_in_tail == _in_head) {
                /* Should probably never hit this */
                std::cerr << "Attempted to read empty buffer\n";
                return 0;
        }
        return _in_buf[_in_tail];
}


/** PRINT **/
size_t FakeSerial::write(uint8_t b)
{
        *_out_stream << b;
        flush();
        return 1;
}

size_t FakeSerial::write(const char* s)
{
        return print(s);
}

size_t FakeSerial::write(const uint8_t *buffer, size_t size)
{
        _out_stream->write((char*)buffer, size);
        flush();
        return size;
}

void FakeSerial::flush()
{
        _out_stream->flush();
}

size_t FakeSerial::print(const char* s)
{
        *_out_stream << s;
        flush();
        return strlen(s);
}

size_t FakeSerial::println(const char* s)
{
        *_out_stream << s << '\n';
        flush();
        return strlen(s);
}

size_t FakeSerial::printf(const char* fmt, ...)
{
        va_list args;

        va_start (args, fmt);
        vprintf (fmt, args);
        va_end (args);
        return strlen(fmt); /* This is wrong, but don't care */
}
