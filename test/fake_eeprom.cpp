/** VERSION 205 **/
#include "fake_eeprom.h"

#include <cstdio>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

fake_eeprom::fake_eeprom()
{
        _fd = open("EEPROM_FILE", O_RDWR | O_CREAT, (mode_t) 0666);
        if (_fd == -1) {
                perror("EEPROM_FILE");
                exit(EXIT_FAILURE);
        }

        if (lseek(_fd, _len - 1, SEEK_SET) == -1) {
                perror("lseek");
                exit(EXIT_FAILURE);
        }

        if (::write(_fd, "", 1) != 1) {
                perror("write");
                exit(EXIT_FAILURE);
        }

        _eeprom_ptr = (uint8_t*) mmap(
                 NULL 
                ,_len 
                ,PROT_READ | PROT_WRITE
                ,MAP_SHARED
                ,_fd
                ,0
        );
        if (!_eeprom_ptr) {
                perror("mmap");
                exit(EXIT_FAILURE);
        }
}

fake_eeprom::~fake_eeprom()
{
        munmap(_eeprom_ptr, _len);
        close(_fd);
}

uint8_t* fake_eeprom::begin()
{
        return _eeprom_ptr;
}

uint8_t* fake_eeprom::end()
{
        return _eeprom_ptr + _len;
}

uint16_t fake_eeprom::length()
{
        return _len;
}

uint8_t fake_eeprom::read(int idx)
{
        return _eeprom_ptr[idx];
}

void fake_eeprom::write(int idx, uint8_t val)
{
        _eeprom_ptr[idx] = val;
        msync(_eeprom_ptr + idx, 1, MS_SYNC);
}

void fake_eeprom::update(int idx, uint8_t val)
{
        if (_eeprom_ptr[idx] != val) {
                write(idx, val);
        }
}
