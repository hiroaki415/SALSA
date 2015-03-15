typedef enum {
    LOGGER = 0,
    DEBUG = 1
} SALSA_BEHAVIOR;

typedef enum {
    BOOTING       = 0,
    READY         = 1,
    LOGGING       = 2,
    FILEOPERATION = 3,
    EXIT          = 4
} SALSA_STATUS_FLAG;

typedef struct {
    //dynamic
    SALSA_STATUS_FLAG status;

    uint16_t x_value;
    uint16_t y_value;
    uint16_t z_value;

    uint8_t led_pin;

    //static
    uint8_t mode;
    uint8_t led_flag

    uint8_t x_lsb;
    uint8_t x_msb;
    uint8_t y_lsb;
    uint8_t y_msb;
    uint8_t z_lsb;
    uint8_t z_msb;

} salsa_status_t;

void salsa_init(SALSA_BEHAVIOR sb);
int load(salsa_status_t *sta, char *filepath);
