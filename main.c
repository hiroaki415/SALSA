#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "src/salsa.h"
#include "lib/parson/parson.h"

void help(void);

int main(int argc, char *argv[]){

    int opt;
    char flag, *path;

    flag = 'o';
    path = "settings.json";

    FILE *file = fopen(path, "r");
    char json[8192] = "";
    char buff[100];
    while(fgets(buff,sizeof(buff),file)!=NULL){
        strcat(json, buff);
    }

    printf("%s",json);

    JSON_Value *jval = json_parse_string_with_comments(json);
    printf("jval\n");
    JSON_Object *jobj = json_value_get_object(jval);
    printf("jobj\n");
    printf("%s\n",json_object_get_name(jobj,10));

    while((opt=getopt(argc,argv,"sdhl:"))!=-1){
        switch(opt){
            case 's':
                if(flag != 'd'){
                    flag = 's';
                }
                break;
            case 'd':
                flag = 'd';
                break;
            case 'h':
                help();
                return 0;
            case 'l':
                path = optarg;
                break;
            default :
                help();
                return 0;
        }
    }

    if(flag=='s'){
        salsa_start(LOGGER, path);
    }else if(flag=='d'){
        salsa_start(DEBUG, path);
    }else{
        help();
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
