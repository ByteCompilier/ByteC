//classic vm emulator for 8 bit processor

#include <stdio.h>//include stdio.h library
#include <string.h> // include string.h library
#include <stdint.h>
#include <stdlib.h> //include stdint.h library

#define COMMAND_SIZE 256 // our one command size
#define COMMAND_NAME 50//our command name
#define ARG1 2//our command first argument
#define ARG2 50//our command second argument

int main(int argc, char *argv[]){//main function
    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        printf("Version alpha 2!");
        return 0;
    }
    else if (argc ==1) {
        printf("Command line args error!\n");
        return 1;
    }
    char command[COMMAND_SIZE]; // our command buffer
    char command_name[COMMAND_SIZE];//our command name var
    char arg1[ARG1];
    char arg2[ARG2];
    uint8_t registres[5] = {0};
    FILE *pfile = fopen(argv[1], "r");//opens file in read mode
    if(pfile == NULL) {//if file dont opened we return 1
        printf("Error opening file\n");//printing error
        return 1;
    }
    //if file opened successfully
    while (fgets(command, COMMAND_SIZE, pfile) != NULL) {// input one command for testing
        sscanf(command, "%s %s %s",command_name, arg1, arg2 );
        if (strcmp(command_name, "MOV") == 0) {
            if (arg1[0] == 'a') {
                int put = atoi(arg2);
                if (arg2[0] == 'a') {
                    registres[0] = registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[0] = registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[0] = registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[0] = registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[0] = registres[4];
                }
                else {
                    registres[0] = put;
                }
            }
            else if (arg1[0] == 'b') {
                int put = atoi(arg2);
                if (arg2[0] == 'a') {
                    registres[1] = registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[1] = registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[1] = registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[1] = registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[1] = registres[4];
                }
                else {
                    registres[1] = put;
                }
            }
            else if (arg1[0] == 'c') {
                int put = atoi(arg2);
                if (arg2[0] == 'a') {
                    registres[2] = registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[2] = registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[2] = registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[2] = registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[2] = registres[4];
                }
                else {
                    registres[2] = put;
                }
            }
            else if (arg1[0] == 'd') {
                int put = atoi(arg2);
                if (arg2[0] == 'a') {
                    registres[3] = registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[3] = registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[3] = registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[3] = registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[3] = registres[4];
                }
                else {
                    registres[3] = put;
                }
            }
            else if (arg1[0] == 'e') {
                int put = atoi(arg2);
                if (arg2[0] == 'a') {
                    registres[4] = registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[4] = registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[4] = registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[4] = registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[4] = registres[4];
                }
                else {
                    registres[4] = put;
                }
            }
        }
        else if (strcmp(command_name, "ADD") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] += registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[0] += registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[0] += registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[0] += registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[0] += registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[0] += put;
                }
            }
            else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] += registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[1] += registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[1] += registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[1] += registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[1] += registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[1] += put;
                }
            }
            else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] += registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[2] += registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[2] += registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[2] += registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[2] += registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[2] += put;
                }
            }
            else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] += registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[3] += registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[3] += registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[3] += registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[3] += registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[3] += put;
                }
            }
            else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] += registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[4] += registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[4] += registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[4] += registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[4] += registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[4] += put;
                }
            }
        }
        else if (strcmp(command_name, "MUL") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] *= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[0] *= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[0] *= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[0] *= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[0] *= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[0] *= put;
                }
            }
            else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] *= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[1] *= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[1] *= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[1] *= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[1] *= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[1] *= put;
                }
            }
            else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] *= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[2] *= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[2] *= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[2] *= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[2] *= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[2] *= put;
                }
            }
            else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] *= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[3] *= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[3] *= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[3] *= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[3] *= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[3] *= put;
                }
            }
            else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] *= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[4] *= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[4] *= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[4] *= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[4] *= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[4] *= put;
                }
            }
        }
        else if (strcmp(command_name, "SUB") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] -= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[0] -= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[0] -= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[0] -= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[0] -= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[0] -= put;
                }
            }
            else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] -= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[1] -= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[1] -= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[1] -= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[1] -= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[1] -= put;
                }
            }
            else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] -= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[2] -= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[2] -= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[2] -= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[2] -= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[2] -= put;
                }
            }
            else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] -= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[3] -= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[3] -= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[3] -= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[3] -= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[3] -= put;
                }
            }
            else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] -= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[4] -= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[4] -= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[4] -= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[4] -= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[4] -= put;
                }
            }
        }
        else if (strcmp(command_name, "DIV") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] /= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[0] /= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[0] /= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[0] /= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[0] /= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[0] /= put;
                }
            }
            else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] /= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[1] /= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[1] /= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[1] /= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[1] /= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[1] /= put;
                }
            }
            else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] /= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[2] /= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[2] /= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[2] /= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[2] /= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[2] /= put;
                }
            }
            else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] /= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[3] /= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[3] /= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[3] /= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[3] /= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[3] /= put;
                }
            }
            else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] /= registres[0];
                }
                else if (arg2[0] == 'b') {
                    registres[4] /= registres[1];
                }
                else if (arg2[0] == 'c') {
                    registres[4] /= registres[2];
                }
                else if (arg2[0] == 'd') {
                    registres[4] /= registres[3];
                }
                else if (arg2[0] == 'e') {
                    registres[4] /= registres[4];
                }
                else {
                    int put = atoi(arg2);
                    registres[4] /= put;
                }
            }
        }
        else if (strcmp(command_name, "NEG") == 0) {
            if (arg1[0] == 'a') {
                registres[0] = registres[0] - (registres[0] * 2);
            }
            else if (arg1[0] == 'b') {
                registres[1] = registres[1] - (registres[1] * 2);
            }
            else if (arg1[0] == 'c') {
                registres[2] = registres[2] - (registres[2] * 2);
            }
            else if (arg1[0] == 'd') {
                registres[3] = registres[3] - (registres[3] * 2);
            }
            else if (arg1[0] == 'e') {
                registres[4] = registres[4] - (registres[4] * 2);
            }
        }
        else if (strcmp(command_name, "INC") == 0) {
            if (arg1[0] == 'a') {
                registres[0] += 1;
            }
            else if (arg1[0] == 'b') {
                registres[1] += 1;
            }
            else if (arg1[0] == 'c') {
                registres[2] += 1;
            }
            else if (arg1[0] == 'd') {
                registres[3] += 1;
            }
            else if (arg1[0] == 'e') {
                registres[4] += 1;
            }
            else {
                printf("Register not found\n");
            }
        }
        else if (strcmp(command_name, "DEC") == 0) {
            if (arg1[0] == 'a') {
                registres[0] -= 1;
            }
            else if (arg1[0] == 'b') {
                registres[1] -= 1;
            }
            else if (arg1[0] == 'c') {
                registres[2] -= 1;
            }
            else if (arg1[0] == 'd') {
                registres[3] -= 1;
            }
            else if (arg1[0] == 'e') {
                registres[4] -= 1;
            }
            else {
                printf("Register not found\n");
            }
        }
        else if (strcmp(command_name, "PR") == 0) {
            if (arg1[0] == 'a') {
                int put = registres[0];
                printf("%d\n", put);
            }
            else if (arg1[0] == 'b') {
                int put = registres[1];
                printf("%d\n", put);
            }
            else if (arg1[0] == 'c') {
                int put = registres[2];
                printf("%d\n", put);
            }
            else if (arg1[0] == 'd') {
                int put = registres[3];
                printf("%d\n", put);
            }
            else if (arg1[0] == 'e') {
                int put = registres[4];
                printf("%d\n", put);
            }
        }
    }
    fclose(pfile);
    pfile = NULL;
    return 0;
}
