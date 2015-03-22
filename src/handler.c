#include "handler.h"
#include "salsa.h"
#include "collector.h"
#include "log.h"

salsa_status_t *status;
Log_File *logfile;

void handler_init(salsa_status_t *sta, Log_File *lf){
    status = sta;
    logfile = lf;
}

void gpio_irq_handler(void){
    collect(status);
    log_printf(logfile, status->x_value, status->y_value, status->z_value);
    log_flush(logfile);
}
