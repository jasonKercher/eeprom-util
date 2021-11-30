/**
 * Quick program used to dump the simulator's
 * EEPROM file. Only non-zero values print.
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main()
{
        FILE* eeprom = fopen("EEPROM_FILE", "r");
        if (!eeprom) {
                perror("EERPOM_FILE");
                exit(EXIT_FAILURE);
        }


        int c = 0;
        int offset = 0;
        unsigned i = 0;
        long val = 0;
        uint8_t* data_ptr = (uint8_t*) &val;
        
        while((c = fgetc(eeprom)) != EOF) {
                *data_ptr++ = (uint8_t) c;

                if (++i < sizeof(long)) {
                        continue;
                }

                if (val != 0) {
                        printf("VALUE #%d: %lu\n", offset, val);
                } 

                /* reset */
                i = 0;
                val = 0;
                data_ptr = (uint8_t*) &val;

                ++offset;
        }
        return 0;
}
