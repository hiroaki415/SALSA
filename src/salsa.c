#include <stdio.h>
#include <stdint.h>
#include "../lib/parson/parson.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "util.h"
#include "debug.h"

#define AT 1
#define MT 0

salsa_status_t status_t;

void salsa_init(SALSA_BEHAVIOR sb){
    switch(sb){
        case LOGGER:
            printf("start");
            break;
        case DEBUG:
            debug_init(&status_t);
            while(status_t.status!=4){
                debug_wait();
            }
    }
}

int load(salsa_status_t *sta, char *filepath){

    JSON_Value *jval;
    JSON_Object *jobj;
    JSON_Array *jarr;

    if ((jval = json_parse_file_with_comments(filepath)) == NULL){
        printf("can not find %s \n",filepath);
        return 0;
    }

    return 0;
}
