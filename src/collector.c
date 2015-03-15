#include <stdint.h>
#include "salsa.h"
#include "sensor.h"

uint16_t tmp;

void collect(salsa_status_t *status){

    tmp = sensor_read(status->x_msb);
    status->x_value = ( tmp << 8 ) | sensor_read(status->x_lsb);

    tmp = sensor_read(status->y_msb);
    status->y_value = ( tmp << 8 ) | sensor_read(status->y_lsb);

    tmp = sensor_read(status->z_msb);
    status->z_value = ( tmp << 8 ) | sensor_read(status->z_lsb);

}
