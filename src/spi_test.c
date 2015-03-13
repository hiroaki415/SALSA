#include <stdio.h>
#include <stdint.h>
#include <wiringPiSPI.h>

int main(void)
{

    uint8_t data[2];
    data[0] = 0x0F | 0b10000000;
    data[1] = 0x00;

    if(wiringPiSPISetup(0,500000)==-1){
        printf("setup failed\n");
    }
    wiringPiSPIDataRW(0,data,2);

    printf("%x\n",data[1]);

    return 0;
}
