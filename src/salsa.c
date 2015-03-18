#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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

void salsa_start(SALSA_BEHAVIOR sb, char *path){

    salsa_status_t *status_t;

    load(status_t, path);
    salsa_init(status_t);

    switch(sb){
        case LOGGER:
            printf("start");
            break;
        case DEBUG:
            debug_init(status_t);
            while(0){
                debug_wait();
            }
    }

}

void salsa_init(salsa_status_t *sta){
    wiringPiSetupGpio();
    sensor_init(0);
    gpio_irq_init(17);
    clock_init(18,sta->sampling_rate);
    pinMode(sta->led_pin, OUTPUT);

    sta->x_value = 0;
    sta->y_value = 0;
    sta->z_value = 0;
    sta->led_flag = 0;
}

void load(salsa_status_t *set_t, char *filepath){

    JSON_Value *jval;
    JSON_Object *jobj;
    JSON_Array *jarr;

    uint8_t tmp;

    char *json = "";
    char buff[100];
    FILE *file = fopen(filepath,"r");
    printf("open\n");
    while(fgets(buff,sizeof(buff),file)!=NULL){
        printf("%s\n",buff);
        json = strcat(json,buff);
    }
    printf("%s\n",json);

    if ((jval = json_parse_file(filepath)) == NULL){
        printf("can not find %s \n",filepath);
        exit(1);
    }

    //loading logger mode
    tmp = (uint8_t)json_object_dotget_boolean(jobj, "logger.mode");
    if(tmp != -1){
       set_t->logger_mode = tmp;
       if(tmp){

           printf("loaded logger mode is Manual-Trigger\n");

           //loading start/end port&pin
//           str = (uint8_t*)json_object_dotget_string(jobj, "logger.manual.start.port");
//           set_t->start_port = get_port_from_str(str);
//           tmp = (uint8_t)json_object_dotget_number(jobj, "logger.manual.start.pin");
//           set_t->start_pin = get_pin_from_number(tmp);
//           str = (uint8_t*)json_object_dotget_string(jobj, "logger.manual.end.port");
//           set_t->end_port = get_port_from_str(str);
//           tmp = (uint8_t)json_object_dotget_number(jobj, "logger.manual.end.pin");
//           set_t->end_pin = get_pin_from_number(tmp);

       }else{

           printf("loaded logger mode is Auto-Trigger\n");

           //loading trigger value
           tmp = (uint8_t)json_object_dotget_number(jobj, "logger.auto.trigger");
           if(tmp != 0){
               set_t->trigger_value = tmp;
               printf("loaded trigger value is %d\n",tmp);
           }else{
               set_t->trigger_value = 167;
               printf("failed loading trigger value\n");
           }

           //loading former length
           tmp = (uint8_t)json_object_dotget_number(jobj, "logger.auto.former");
           if(tmp != 0){
               set_t->former_length = tmp;
               printf("loaded former length is %d\n",tmp);
           }else{
               set_t->former_length = 30;
               printf("failed loading former length\n");
           }

           //loading former length
           tmp = (uint8_t)json_object_dotget_number(jobj, "logger.auto.latter");
           if(tmp != 0){
               set_t->latter_length = tmp;
               printf("loaded latter length is %d\n",tmp);
           }else{
               set_t->former_length = 90;
               printf("failed loading latter length\n");
           }

       }
    }else{
        printf("failed loading logger mode\n");
    }

    //loading sampling rate
    tmp = (uint8_t)json_object_dotget_number(jobj, "logger.rate");
    if(tmp != 0){
        set_t->sampling_rate = tmp;
        printf("loaded sampling rate is %d\n",tmp);
    }else{
        printf("failed loading sampling rate\n");
    }

    set_t->led_pin = json_object_get_number(jobj,"led_pin");

    //loading acc sensor setting
    set_t->x_lsb = (uint8_t)json_object_dotget_number(jobj, "acc.x.lsb");
    set_t->x_msb = (uint8_t)json_object_dotget_number(jobj, "acc.x.msb");
    set_t->y_lsb = (uint8_t)json_object_dotget_number(jobj, "acc.y.lsb");
    set_t->y_msb = (uint8_t)json_object_dotget_number(jobj, "acc.y.msb");
    set_t->z_lsb = (uint8_t)json_object_dotget_number(jobj, "acc.z.lsb");
    set_t->z_msb = (uint8_t)json_object_dotget_number(jobj, "acc.z.msb");

    //loading writing data to acc register
    jarr = json_object_get_array(jobj, "register");
    set_t->amount = json_array_get_count(jarr);
    int i = 0;
    for(i = 0; i < json_array_get_count(jarr); i++){
        jobj = json_array_get_object(jarr, i);
        set_t->address[i] = (uint8_t)json_object_get_number(jobj, "address");
        set_t->data[i] = (uint8_t)json_object_get_number(jobj, "data");
    }

    printf("finished load setting\n");

}
