#include <stdio.h>
#include <stdint.h>
#include "debug.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "util.h"

char buff;
uint8_t num0;
uint8_t num1;

salsa_status_t *status;

void debug_init(salsa_status_t *sta){
    status = sta;
}

void debug_wait(void){

    printf("debug@SALSA >>> ");
    scanf("%c%x%x", &buff, &num0, &num1);
    printf("\n");

    parse();

}

void parse(void){
    switch(buff){
        case 'r':
            printf("%x\n",sensor_read(num0));
            break;
        case 'w':
            sensor_write(num0, num1);
            break;
        case 'c':
            collect(status);
            break;
        case 'l':
            write_led(status, num0);
            break;
        case 't':
            toggle_led(status);
            break;
        case 'h':
            debug_help();
            break;
        default :
            printf("incorrect command!\n");
            debug_help();
            break;
    }
}

void debug_help(void){
    printf(
            "===SALSA debug mode===\n"
            "enter command to debug\n"
            "\n"
            "  r [ADDRESS(HEX)]               read from sensor at [ADDRESS(HEX)]\n"
            "  w [ADDRESS(HEX)] [DATA(HEX)]   write [DATA(HEX)] int sensor at [ADDRESS(HEX)]\n"
            "  c                              collect all data\n"
            "  l [BIT]                        led on or off ( [BIT] 0:off  1:on)\n"
            "  t                              toggle led flash\n"
            "  h                              help message\n"
            );
}
