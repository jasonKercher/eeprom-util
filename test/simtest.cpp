/** VERSION 205 **/
#include <iostream>
#include <getopt.h>

#include "fake_arduino.h"

static const char* help_string = "no help here\n";

void parseargs(char c)
{
        switch (c) {
        case 'h':
                puts(help_string);
                exit(0);
        case 'v':
                break;
        default:
                abort();
        }
}


int main(int argc, char** argv) 
{
        static struct option long_options[] =
        {
                /* long option, (no) arg, 0, short option */
                {"help", no_argument, 0, 'h'},
                {"verbose", no_argument, 0, 'v'},
                {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;
        int c = 0;

        while ( (c = getopt_long (argc, argv, "hv",
                                  long_options, &option_index)) != -1)
                        parseargs(c);

        setup();
        for(;;)
                loop();
}
