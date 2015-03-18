#ifndef _IRQ
#define _IRQ

void gpio_irq_init(int pin);
void gpio_irq_handler(void);
void my_init(void);

#endif
