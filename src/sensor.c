#include <stdint.h>
#include <wiringPiSPI.h>
#include "sensor.h"
#include "salsa.h"

int read_flag = 0b10000000;
int write_flag = 0b00000000;
uint8_t data[2];

void sensor_init(int device){
    wiringPiSPISetup(device,500000);
}

uint8_t sensor_read(uint8_t address){

    data[0] = address | read_flag;
    data[1] = 0x00; // dummy tx

    wiringPiSPIDataRW(0,data,2);

    return data[1];
}

void sensor_write(uint8_t address, uint8_t byte){

    data[0] = address | write_flag;
    data[1] = byte;

    wiringPiSPIDataRW(0,data,2);
}
