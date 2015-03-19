#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "src/salsa.h"
#include "lib/parson/parson.h"

void help(void);

int main(int argc, char *argv[]){
    test_start();
    int opt;
    char flag;
    char *path;

    flag = 'o';
    path = "settings.json";

    while((opt=getopt(argc,argv,"sdhl:"))!=-1){
        switch(opt){
            case 's':
                if(flag != 'd'){
                    printf("char S!!!\n");
                    flag = 's';
                    printf("chaaaaaaaaaaaaaaaaaaaaaaaar!!!\n");
                }
                break;
            case 'd':
                printf("char D!!!\n");
                flag = 'd';
                printf("chaaaaaaaaaaaaaaaaaaaaar!!!\n");
                break;
            case 'h':
                help();
                exit(0);
            case 'l':
                path = optarg;
                break;
            default :
                help();
                exit(0);
        }
    }

    switch(flag){
        case 's':
            salsa_start(LOGGER, path);
            break;
        case 'd':
            printf("debug!\n");
            salsa_start(DEBUG, path);
            break;
        default :
            help();
            exit(0);
    }

    return 0;
}

void help(void){
    printf(
            "SALSA is Accelerometer Logger Software on Raspberry Pi\n"
            "\n"
            "USAGE: salsa [OPTION] [-l SETTING_FILE_TO_LOAD]\n"
            "\n"
            "OPTIONS are below:\n"
            "  -s           start salsa software system\n"
            "  -d           debug test for spi connection or else\n"
            "  -h           help message\n"
            "  -l <FILE>    load setting file of <FILE>\n"
            );
}
