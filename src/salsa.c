#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include "../lib/parson/parson.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "irq.h"
#include "clock.h"
#include "util.h"
#include "debug.h"

#define AT 1
#define MT 0

salsa_status_t status_t;

void salsa_start(SALSA_BEHAVIOR sb, char *path){
    load(&status_t, path);
    salsa_init();
    switch(sb){
        case LOGGER:
            printf("start");
            break;
        case DEBUG:
            debug_init(&status_t);
            while(0){
                debug_wait();
            }
    }
}

void salsa_init(void){
    wiringPiSetupGpio();
    sensor_init(0);
    gpio_irq_init(18);
    clock_init(15,100);
}

void load(salsa_status_t *sta, char *filepath){

    JSON_Value *jval;
    JSON_Object *jobj;
    JSON_Array *jarr;

    if ((jval = json_parse_file_with_comments(filepath)) == NULL){
        printf("can not find %s \n",filepath);
        exit(1);
    }

}
