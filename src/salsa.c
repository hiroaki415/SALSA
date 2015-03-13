#include <stdio.h>
#include "../lib/parson/parson.h"

#define AT 1
#define MT 0

typedef enum {
    BOOTING       = 0,
    READY         = 1,
    LOGGING       = 2,
    FILEOPERATION = 3
} SALSA_STATUS_FLAG;

typedef struct {
    SALSA_STATUS_FLAG status;
    uint8_t mode;
} salsa_status_t;

salsa_status_t status_t;

void init(void){
    printf("hello");
}

int load(salsa_status_t *set, char *filepath){

    JSON_Value *jval;
    JSON_Object *jobj;
    JSON_Array *jarr;

    if ((jval = json_parse_file_with_comments(filepath)) == NULL){
        printf("can not find %s \n",filepath);
        return 0;
    }

    return 0;
}
