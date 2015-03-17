#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <wiringPi.h>
#include "clock.h"

int clock_pin;

void clock_init(int pin, uint16_t freq){
    if(freq<10){
        printf("clock frequecy needs over 10 Hz\n");
        exit(1);
    }
    clock_pin = pin;
    pinMode(clock_pin, PWM_OUTPUT);
    pwmSetRange(1920);
    pwmSetClock(10000/freq);
}

void clock_start(void){
    pwmWrite(clock_pin, 512);
}

void clock_stop(void){
    pwmWrite(clock_pin, 0);
}
