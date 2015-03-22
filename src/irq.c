#include <stdio.h>
#include <wiringPi.h>
#include "irq.h"
#include "salsa.h"
#include "handler.h"

void gpio_irq_init(int pin){
    pinMode(pin, INPUT);
    wiringPiISR(pin, INT_EDGE_RISING, &gpio_irq_handler);
}

void gpio_irq_reset(int pin){
    wiringPiISR(pin, INT_EDGE_RISING, NULL);
}
