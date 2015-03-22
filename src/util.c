#include <wiringPi.h>
#include "salsa.h"

void write_led(salsa_status_t *status, int bit){
    digitalWrite(status->led_pin, bit);
    status->led_flag = bit;
}

void toggle_led(salsa_status_t *status){
    if(status->led_flag){
        write_led(status,0);
    }else{
        write_led(status,1);
    }
}

void status_led(salsa_status_t *status){
    switch(status->flag){
        case READY:
            toggle_led(status);
            delay(500);
            break;
        case LOGGING:
            toggle_led(status);
            delay(100);
            break;
        default:
            write_led(status, 1);
            break;
    }

}
