#include <stdio.h>
#include <wiringPi.h>
#include "irq.h"
#include "salsa.h"

int gpio_irq_pin;

void gpio_irq_init(int pin){
    gpio_irq_pin = pin;
    pinMode(gpio_irq_pin, INPUT);
    wiringPiISR(gpio_irq_pin, INT_EDGE_RISING, &gpio_irq_handler);
}

void gpio_irq_handler(void){
    //do handler
}
