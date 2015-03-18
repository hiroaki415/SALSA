#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "log.h"

void logfile_init(Log_File *lf, char *name, char *format){

    if(lf->file!=NULL){
        log_close(lf);
    }

    lf->name = name;
    lf->file = fopen(lf->name, "w+");
    lf->format = format;
    lf->line = 0;
}

void log_printf(Log_File *lf, ...){
    va_list list;
    va_start(list, lf->format);
    log_vprintf(lf,  list);
    va_end(list);
}

void log_vprintf(Log_File *lf, va_list list){
    vfprintf(lf->file, lf->format, list);
    fputc('\n', lf->file);
    lf->line++;
}

void log_flush(Log_File *lf){
    fflush(lf->file);
}

void log_close(Log_File *lf){
    fclose(lf->file);
}

void log_slice(Log_File *lf, char *outfile, long lines){

    FILE *output = fopen(outfile, "w+");

    char buff[100];
    long count = 0;
    long offsetline = lf->line - lines;

    // move to startline
    while( ( fgets(buff, sizeof(buff), lf->file)  != NULL ) && ( count < (offsetline) ) ){
        count++;
    }

    //cloning
    while( fgets(buff, sizeof(buff), lf->file) != NULL){
        fputs(buff, output);
    }

    fclose(output);

}
