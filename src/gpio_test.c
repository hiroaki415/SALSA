#include <stdio.h>
#include <wiringPi.h>

unsigned int counter = 0;

void incre(void){
    counter++;
}

int main (void)
{
  printf ("Raspberry Pi blink\n") ;

  if (wiringPiSetupGpio () == -1)
    return 1 ;

  pinMode (18, PWM_OUTPUT) ;         // aka BCM_GPIO pin 17
  pwmSetMode(PWM_MODE_MS) ;
  pwmSetClock(41) ;
  pwmSetRange(4095) ;

  pinMode (17, INPUT) ;
  wiringPiISR(17, INT_EDGE_RISING, &incre) ;

  pwmWrite(18, 512) ;
  delay(1000);

  printf("%d\n", counter) ;
  return 0 ;
}
