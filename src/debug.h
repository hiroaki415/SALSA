#include "salsa.h"

#ifndef _DEBUG
#define _DEBUG

void debug_init(salsa_status_t *sta);
void debug_wait(void);
void parse(char *buff);
void debug_help(void);

#endif
