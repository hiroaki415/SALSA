#ifndef _HANDLER
#define _HANDLER

#include "salsa.h"
#include "log.h"

void handler_init(salsa_status_t *sta, Log_File *lf);
void gpio_irq_handler(void);

#endif
