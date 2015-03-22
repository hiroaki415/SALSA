#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "debug.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "util.h"

salsa_status_t *status;

void debug_init(salsa_status_t *sta){
    status = sta;
}

void debug_wait(void){

    char *buff;

    printf("debug@SALSA >>> ");
    scanf("%s", buff);

    parse(buff);

}

void parse(char *buff){

    unsigned int num0;
    unsigned int num1;


    if(strcmp(buff,"read")==0){

        printf("enter address to read : ");
        scanf("%x",&num0);
        printf("read value is %x at %x \n", sensor_read(num0), num0);

    }else if(strcmp(buff,"write")==0){

        printf("enter address to write : ");
        scanf("%x",&num0);
        printf("enter data to write : ");
        scanf("%x",&num1);

        sensor_write(num0, num1);
        printf("write %x at %x \n", num1, num0);

    }else if(strcmp(buff,"collect")==0){

        collect(status);
        printf("x:%6d y:%6d z:%6d\n", status->x_value , status->y_value ,status->z_value);

    }else if(strcmp(buff,"led")==0){

        printf("enter bit to write into led pin : ");
        scanf("%d",&num0);
        write_led(status, num0);
        printf("write bit %d, check your led out\n", num0);

    }else if(strcmp(buff,"toggle")==0){

        toggle_led(status);
        printf("bit toggled, check your led out\n");

    }else if(strcmp(buff,"help")==0){

        debug_help();

    }else if(strcmp(buff,"exit")==0){

        printf("exit SALSA debug mode...\n");
        salsa_exit(0);

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
            "  read         read from sensor on SPI bus\n"
            "  write        write data into sensor on SPI bus\n"
            "  collect      collect all data\n"
            "  led          led on or off\n"
            "  toggle       toggle led flash\n"
            "  help         help message\n"
            "  exit         exit SALSA debug mode\n"
            );
}
