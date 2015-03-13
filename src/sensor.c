#include <stdint.h>
#include <salsa.h>
#include <wiringPiSPI.h>

int read_flag = 0b10000000;
int write_flag = 0b00000000;
uint8_t data[2];

void sensor_init(int device){
    wiringPiSPISetup(device,500000);
}

uint8_t read(uint8_t address){

    data[0] = address | read_flag;
    data[1] = 0x00; // dummy tx

    wiringPiSPIDataRW(0,data,2);

    return data[1];
}

void write(uint8_t address, uint8_t byte){

    data[0] = address | write_flag;
    data[2] = byte;

    wiringPiSPIDataRW(0,data,2);
}
