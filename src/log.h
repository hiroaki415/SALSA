#ifndef _LOG
#define _LOG

typedef struct {
    FILE *file;
    char *name;
    char *format;
    int line;
} Log_File;

void logfile_init(Log_File *lf, char *name, char *format);
void log_printf(Log_File *lf, ...);
void log_vprintf(Log_File *lf, va_list list);
void log_flush(Log_File *lf);
void log_close(Log_File *lf);

#endif
