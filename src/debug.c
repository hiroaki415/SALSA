#include <stdio.h>
#include <stdint.h>
#include "debug.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "util.h"

char *buff;
uint8_t num0;
uint8_t num1;

salsa_status_t *status;

void debug_init(salsa_status_t *sta){
    status = sta;
}

void debug_wait(void){

    printf("debug@SALSA >>> ");
    scanf("%s%x%x", &buff, &num0, &num1);
    printf("\n");

    parse();

}

void parse(void){
    if(strcmp(buff,"read")==0){
        printf("%x\n",sensor_read(num0));
    }else if(strcmp(buff,"write")==0){
        sensor_write(num0, num1);
    }else if(strcmp(buff,"collect")==0){
        collect(status);
    }else if(strcmp(buff,"led")==0){
        write_led(status, num0);
    }else if(strcmp(buff,"toggle")==0){
        toggle_led(status);
    }else if(strcmp(buff,"help")==0){
        debug_help();
    }else{
        printf("incorrect command!\n");
        debug_help();
    }
}

void debug_help(void){
    printf(
            "===SALSA debug mode===\n"
            "enter command to debug\n"
            "\n"
            "  read [ADDRESS(HEX)]                 read from sensor at [ADDRESS(HEX)]\n"
            "  write [ADDRESS(HEX)] [DATA(HEX)]    write [DATA(HEX)] int sensor at [ADDRESS(HEX)]\n"
            "  collect                             collect all data\n"
            "  led [BIT]                           led on or off ( [BIT] 0:off  1:on)\n"
            "  toggle                              toggle led flash\n"
            "  help                                help message\n"
            );
}
