/** VERSION 205 **/
#ifndef EEPROM_H
#define EEPROM_H

#include <stdlib.h>
#include <inttypes.h>

class fake_eeprom {
private:
        uint8_t* _eeprom_ptr = NULL;
        int _fd = 0;
        /* teensy 4.1 */
        //const unsigned _len = 4284;
        /* teensy 4.0 */
        const unsigned _len = 1080;
public:
        fake_eeprom();
        ~fake_eeprom();
        uint8_t* begin();    
        uint8_t* end();      
        uint16_t length();
        uint8_t read(int idx);
        void write(int idx, uint8_t val);
        void update(int idx, uint8_t val);

        template<typename T> 
        T &get(int idx, T &data)
        {
                uint8_t* eeprom_ptr = _eeprom_ptr + idx;
                uint8_t* data_ptr = (uint8_t*) &data;
                for (unsigned i = 0; i < sizeof(T); ++i, ++eeprom_ptr) {
                        *data_ptr++ = *eeprom_ptr;
                }
                return data;
        }
        
        template<typename T> 
        const T &put(int idx, const T &data)
        {
                uint8_t* eeprom_ptr = _eeprom_ptr + idx;
                uint8_t* data_ptr = (uint8_t*) &data;
                for (unsigned i = 0; i < sizeof(T); ++i, ++eeprom_ptr) {
                        update(idx + i, (*data_ptr));
                        ++data_ptr;
                }
                return data;
        }
};

static fake_eeprom EEPROM;

typedef fake_eeprom EEPROMClass;

#endif   /* EEPROM_H */
