#include <stdint.h>

#ifndef _SALSA
#define _SALSA

typedef enum {
    LOGGER = 0,
    DEBUG = 1
} SALSA_BEHAVIOR;

typedef enum {
    BOOTING       = 0,
    READY         = 1,
    LOGGING       = 2,
    FILEOPERATION = 3,
} SALSA_STATUS_FLAG;

typedef struct {

    /*dynamic*/
    SALSA_STATUS_FLAG flag;

    uint16_t x_value;
    uint16_t y_value;
    uint16_t z_value;

    uint8_t led_flag;



    /* static */
    // logger
    uint8_t logger_mode;
    uint8_t sampling_rate;
    uint16_t trigger_value;
    uint8_t former_length;
    uint8_t latter_length;

    // sensor
    uint8_t x_lsb;
    uint8_t x_msb;
    uint8_t y_lsb;
    uint8_t y_msb;
    uint8_t z_lsb;
    uint8_t z_msb;

    uint8_t amount;
    uint8_t address[10];
    uint8_t data[10];

    // other
    uint8_t led_pin;

} salsa_status_t;

void salsa_start(SALSA_BEHAVIOR sb, char *path);
void salsa_init(salsa_status_t *sta);
void salsa_exit(int sig);
void load(salsa_status_t *sta, char *filepath);

#endif
