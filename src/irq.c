#include <stdio.h>
#include <wiringPi.h>
#include "irq.h"
#include "salsa.h"
#include "collector.h"
#include "log.h"

int gpio_irq_pin;

//Log_File *lf;

void gpio_irq_init(int pin){
    gpio_irq_pin = pin;
    pinMode(gpio_irq_pin, INPUT);
    wiringPiISR(gpio_irq_pin, INT_EDGE_RISING, &gpio_irq_handler);
}

void gpio_irq_handler(void){
    //do handler
    //log_printf(lf, 5, 6, 7);
    //log_flush(lf);
}

void my_init(void){
    char *name = "tmp.txt";
    char *format = "%d %d %d";
    //logfile_init(lf, name, format);
}
