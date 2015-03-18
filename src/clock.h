#ifndef _CLOCK
#define _CLOCK

void clock_init(int pin, uint16_t freq);
void clock_start(void);
void clock_stop(void);

#endif
