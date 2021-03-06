#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <wiringPi.h>
#include "../lib/parson/parson.h"
#include "salsa.h"
#include "sensor.h"
#include "collector.h"
#include "irq.h"
#include "handler.h"
#include "clock.h"
#include "log.h"
#include "util.h"
#include "debug.h"

#define AT 0
#define MT 1

void salsa_start(SALSA_BEHAVIOR sb, char *path){

    printf("SALSA initializing...\n");

    salsa_status_t *status_t = malloc(sizeof(salsa_status_t));

    load(status_t, path);
    salsa_init(status_t);

    switch(sb){
        case LOGGER:
            {

                printf("prepare for log file...\n");

                Log_File *logfile;
                logfile = malloc(sizeof(Log_File));
                logfile_init(logfile, "tmp.txt", "%d %d %d\n");
                handler_init(status_t, logfile);
                gpio_irq_init(17);

                printf("all setting is done\n");
                printf("logger start!!!\n");

                status_t->flag = LOGGING;
                clock_start();

                while(1){
                        status_led(status_t);
                    }
                break;
            }
        case DEBUG:
            {
                debug_init(status_t);
                while(1){
                    debug_wait();
                }
            }
    }

}

void salsa_init(salsa_status_t *sta){
    sta->flag = BOOTING;
    wiringPiSetupGpio();
    sensor_init(0);
    clock_init(18,sta->sampling_rate);
    pinMode(sta->led_pin, OUTPUT);
    write_led(sta, 1);

    int i;
    for(i = 0; i < sta->amount; i++){
        sensor_write(sta->address[i], sta->data[i]);
    }

    signal(SIGINT, &salsa_exit);
    signal(SIGKILL, &salsa_exit);

    sta->x_value = 0;
    sta->y_value = 0;
    sta->z_value = 0;

    sta->flag = READY;
}

void salsa_exit(int sig){
    printf("exiting salsa system...\n");
    gpio_irq_reset(17);
    pinMode(18,INPUT);
    exit(0);
}

void load(salsa_status_t *set_t, char *filepath){

    JSON_Value *jval;
    JSON_Object *jobj;
    JSON_Array *jarr;

    const char *tmps;
    uint8_t tmpi;

    printf("now loading %s ...\n", filepath);

    if ((jval = json_parse_file_with_comments(filepath)) == NULL){
        printf("fail to load %s \n",filepath);
        printf("please check your file directory, json syntax or else\n");
        exit(1);
    }
    jobj = json_value_get_object(jval);

    //loading logger mode
    tmpi = json_object_dotget_boolean(jobj, "logger.mode");
    if(tmpi != -1){
//       set_t->logger_mode = tmpi;
       if(tmpi){

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
           tmps = json_object_dotget_string(jobj, "logger.auto.trigger");
           if(tmps != 0){
               set_t->trigger_value = atoi(tmps);
               printf("loaded trigger value is %s\n",tmps);
           }else{
               set_t->trigger_value = 167;
               printf("failed loading trigger value\n");
           }

           //loading former length
           tmps = json_object_dotget_string(jobj, "logger.auto.former");
           if(tmps != 0){
               set_t->former_length = atoi(tmps);
               printf("loaded former length is %s\n",tmps);
           }else{
               set_t->former_length = 30;
               printf("failed loading former length\n");
           }

           //loading former length
           tmps = json_object_dotget_string(jobj, "logger.auto.latter");
           if(tmps != 0){
               set_t->latter_length = atoi(tmps);
               printf("loaded latter length is %s\n",tmps);
           }else{
               set_t->former_length = 90;
               printf("failed loading latter length\n");
           }

       }
    }else{
        printf("failed loading logger mode\n");
    }

    //loading sampling rate
    tmps = json_object_dotget_string(jobj, "logger.rate");
    if(tmps != NULL){
        set_t->sampling_rate = atoi(tmps);
        printf("loaded sampling rate is %s\n",tmps);
    }else{
        printf("failed loading sampling rate\n");
    }

    tmps = json_object_get_string(jobj,"led_pin");
    if(tmps != NULL){
        set_t->led_pin = atoi(tmps);
        printf("debug led pin is %s\n", tmps);
    }else{
        set_t->led_pin = 24;
        printf("failed loading led pin\n");
    }

    //loading acc sensor setting
    char *e;
    tmps = json_object_dotget_string(jobj,"acc.x.lsb");
    printf("acc x lsb is  %s\n", tmps);
    set_t->x_lsb = strtol(tmps, &e, 16);

    tmps = json_object_dotget_string(jobj,"acc.x.msb");
    printf("acc x msb is  %s\n", tmps);
    set_t->x_msb = strtol(tmps, &e, 16);

    tmps = json_object_dotget_string(jobj,"acc.y.lsb");
    printf("acc y lsb is  %s\n", tmps);
    set_t->y_lsb = strtol(tmps, &e, 16);

    tmps = json_object_dotget_string(jobj,"acc.y.msb");
    printf("acc y msb is  %s\n", tmps);
    set_t->y_msb = strtol(tmps, &e, 16);

    tmps = json_object_dotget_string(jobj,"acc.z.lsb");
    printf("acc z lsb is  %s\n", tmps);
    set_t->z_lsb = strtol(tmps, &e, 16);

    tmps = json_object_dotget_string(jobj,"acc.z.msb");
    printf("acc z msb is  %s\n", tmps);
    set_t->z_msb = strtol(tmps, &e, 16);


    //loading writing data to acc register
    jarr = json_object_get_array(jobj, "register");
    set_t->amount = json_array_get_count(jarr);
    int i = 0;
    for(i = 0; i < json_array_get_count(jarr); i++){
        jobj = json_array_get_object(jarr, i);
        set_t->address[i] = strtol(json_object_dotget_string(jobj, "address"), &e, 16);
        set_t->data[i] = strtol(json_object_dotget_string(jobj, "data"), &e, 16);
    }

    printf("finished load setting\n");

}
