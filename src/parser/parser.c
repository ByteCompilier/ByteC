#include <stdio.h>

void parser(char *array,char *command_name, char *arg1, char *arg2, char *arg3) {
    sscanf(array, "%s %s %s %s", command_name, arg1, arg2, arg3);
}
