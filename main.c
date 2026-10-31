//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT


//classic vm emulator for 8 bit processor
#include <stdio.h>//include stdio.h library
#include <string.h> // include string.h library
#include <stdint.h>
#include <stdlib.h> //include stdint.h library

#define COMMAND_SIZE 256 // our one command size
#define COMMAND_NAME 50//our command name
#define ARG1 50//our command first argument
#define ARG2 50//our command second argument
#define ARG3 50
#define STACK_SIZE 10000
#define ARG_SIZE 2

int main(int argc, char *argv[]){//main function
    int stroke_count = 0;
    long return_stack[STACK_SIZE];
    int stack_pointer = -1;

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        printf("Version alpha 6!");
        return 0;
    }
    else if (argc ==1) {
        printf("Command line args error!\n");
        return 1;
    }
    int64_t registers_copy[5] = {0};
    char command[COMMAND_SIZE]; // our command buffer
    char command_name[COMMAND_SIZE];//our command name var
    char arg1[ARG1];
    char arg2[ARG2];
    char arg3[ARG3];
    char labels[5000][100];
    int8_t code_if = 0;
    int64_t registres[5] = {0};
    FILE *pfile = fopen(argv[1], "r");//opens file in read mode
    if(pfile == NULL) {//if file dont opened we return 1
        printf("Error opening file\n");//printing error
        return 1;
    }
    //if file opened successfully
    while (fgets(command, COMMAND_SIZE, pfile) != NULL) {// input one command for testing
        sscanf(command, "%s %s %s %s",command_name, arg1, arg2, arg3);
        stroke_count++;
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
            else{
                printf("In line %d\n", stroke_count);
                system("\"C:\\Program Files\\bytec\\bytec\\ERROR1.bat\"");
                exit(1);
            }
        }
        else if (strcmp(command_name, "CMP") == 0) {
            if (strcmp(arg2, "==") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] == registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] == registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] == registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] == registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] == registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] == put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] == registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] == registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] == registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] == registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] == registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] == put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] == registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] == registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] == registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] == registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] == registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] == put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] == registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] == registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] == registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] == registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] == registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] == put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] == registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] == registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] == registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] == registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] == registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] == put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put == put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }

                }
            }
            else if (strcmp(arg2, "<") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] < registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] < registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] < registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] < registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] < registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] < put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] < registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] < registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] < registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] < registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] < registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] < put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] < registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] < registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] < registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] < registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] < registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] < put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] < registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] < registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] < registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] < registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] < registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] < put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] < registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] < registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] < registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] < registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] < registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] < put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put < put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                }
            }
            else if (strcmp(arg2, ">") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] > registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] > registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] > registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] > registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] > registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] > put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] > registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] > registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] > registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] > registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] > registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] > put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] > registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] > registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] > registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] > registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] > registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] > put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] > registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] > registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] > registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] > registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] > registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] > put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] > registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] > registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] > registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] > registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] > registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] > put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put > put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                }
            }
            else if (strcmp(arg2, ">=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] >= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] >= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] >= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] >= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] >= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] >= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] >= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] >= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] >= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] >= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] >= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] >= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] >= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] >= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] >= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] >= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] >= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] >= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] >= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] >= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] >= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] >= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] >= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] >= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] >= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] >= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] >= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] >= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] >= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] >= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put >= put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                }
            }
            else if (strcmp(arg2, "<=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] <= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] <= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] <= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] <= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] <= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] <= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] <= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] <= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] <= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] <= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] <= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] <= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] <= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] <= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] <= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] <= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] <= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] <= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] <= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] <= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] <= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] <= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] <= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] <= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] <= registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] <= registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] <= registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] <= registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] <= registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] <= put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put <= put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                }
            }
            else if (strcmp(arg2, "!=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] != registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[0] != registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[0] != registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[0] != registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[0] != registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[0] != put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] != registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[1] != registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[1] != registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[1] != registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[1] != registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[1] != put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] != registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[2] != registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[2] != registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[2] != registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[2] != registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[2] != put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] != registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[3] != registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[3] != registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[3] != registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[3] != registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[3] != put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] != registres[0]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'b') {
                        if (registres[4] != registres[1]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'c') {
                        if (registres[4] != registres[2]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'd') {
                        if (registres[4] != registres[3]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else if (arg3[0] == 'e') {
                        if (registres[4] != registres[4]) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                    else {
                        int put = atoll(arg3);
                        if (registres[4] != put) {
                            code_if = 1;
                        }
                        else {
                            code_if = 0;
                        }
                    }
                }
                else {
                    int put = atoll(arg1);
                    if (arg3[0] == 'a') {
                        if (put != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (put != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (put != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (put != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (put != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put_r = atoll(arg3);
                        if (put != put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }

                }
            }
        }
        else if (strcmp(command_name, "JIF") == 0) {
            if (code_if == 0) {
                rewind(pfile);
                while (1) {
                    int x = '\0';
                    while (x != ':') {
                        x = fgetc(pfile);
                        if (x == EOF) {
                            goto exit;
                        }
                    }
                    fseek(pfile, 1, SEEK_CUR);
                    for (int i = 0; 1 ==1 ; i++) {
                        char proverka[100];
                        char * status = 0;
                        status = fgets(proverka, sizeof(proverka), pfile);
                        proverka[strcspn(proverka, "\r\n")] = '\0';
                        if (status == NULL) {
                            goto exit;
                        }
                        if (strcmp(proverka, arg1) == 0) {
                            goto exit;
                        }
                        else {
                            break;
                        }
                    }
                }
exit:;
            }
        }
        else if (strcmp(command_name, "JIT") == 0) {
            if (code_if == 1) {
                rewind(pfile);
                while (1) {
                    int x = '\0';
                    while (x != ':') {
                        x = fgetc(pfile);
                        if (x == EOF) {
                            goto hu;
                        }
                    }
                    fseek(pfile, 1, SEEK_CUR);
                    for (int i = 0; 1 ==1 ; i++) {
                        char proverka[100];
                        char * status = 0;
                        status = fgets(proverka, sizeof(proverka), pfile);
                        proverka[strcspn(proverka, "\r\n")] = '\0';
                        if (status == NULL) {
                            goto hu;
                        }
                        if (strcmp(proverka, arg1) == 0) {
                            goto hu;
                        }
                        else {
                            break;
                        }
                    }
                }
                hu:;
            }

        }
        else if (strcmp(command_name, "JMP") == 0) {
            rewind(pfile);
            while (1) {
                int x = '\0';
                while (x != ':') {
                    x = fgetc(pfile);
                    if (x == EOF) {
                        goto label;
                    }
                }
                fseek(pfile, 1, SEEK_CUR);
                for (int i = 0; 1 ==1 ; i++) {
                    char proverka[100];
                    char * status = 0;
                    status = fgets(proverka, sizeof(proverka), pfile);
                    proverka[strcspn(proverka, "\r\n")] = '\0';
                    if (status == NULL) {
                        goto label;
                    }
                    if (strcmp(proverka, arg1) == 0) {
                        goto label;
                    }
                    else {
                        break;
                    }
                }
            }
label:;
        }
        else if (strcmp(command_name, "CALL") == 0) {
            registers_copy[0] = registres[0];
            registers_copy[1] = registres[1];
            registers_copy[2] = registres[2];
            registers_copy[3] = registres[3];
            registers_copy[4] = registres[4];
            stack_pointer++;
            return_stack[stack_pointer] = ftell(pfile);
            rewind(pfile);
            while (1) {
                int x = '\0';
                while (x != ':') {
                    x = fgetc(pfile);
                    if (x == EOF) {
                        goto labelk;
                    }
                }
                fseek(pfile, 1, SEEK_CUR);
                for (int i = 0; 1 ==1 ; i++) {
                    char proverka[100];
                    char * status = 0;
                    status = fgets(proverka, sizeof(proverka), pfile);

                    if (status == NULL) {
                        printf("CALL: label not found: %s\n", arg1);
                        stack_pointer--;
                        fseek(pfile, return_stack[stack_pointer + 1], SEEK_SET);
                        goto labelk;
                    }

                    proverka[strcspn(proverka, "\r\n")] = '\0';
                    if (strcmp(proverka, arg1) == 0) {
                        goto labelk;
                    }
                    else {
                        break;
                    }
                }
            }
            labelk:;
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
            printf("DEBUG ADD: arg1=%s arg2=%s b=%lld\n",
       arg1, arg2, (long long)registres[1]);
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
                else if (strcmp(arg2, 0) == 0) {
                    printf("In line %d\n", stroke_count);
                    system("\"C:\\program files\\bytec\\bytec\\ERROR3.bat\"");
                    exit(1);
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
        else if (strcmp(command_name, "IN") == 0) {
            int number = 0;
            scanf("%d", &number);
            if (arg1[0] == 'a') {
                registres[0] = number;
            }
            else if (arg1[0] == 'b') {
                registres[1] = number;
            }
            else if (arg1[0] == 'c') {
                registres[2] = number;
            }
            else if (arg1[0] == 'd') {
                registres[3] = number;
            }
            else if (arg1[0] == 'e') {
                registres[4] = number;
            }
            else {
                printf("Register not found\n");
            }
        }
        else if (strcmp(command_name, ";") == 0) {
            continue;
        }
        else if (strcmp(command_name, "RET") == 0) {
            printf("DEBUG RET: arg1=%s b=%lld saved_b=%lld\n",
       arg1, (long long)registres[1],
       (long long)registers_copy[1]);
            if (return_stack[stack_pointer] == 0) {
                exit(0);
            }
            fseek(pfile, return_stack[stack_pointer], SEEK_SET);
            return_stack[stack_pointer] = 0;
            stack_pointer--;
            if (strcmp(arg1, "a") == 0) {
                registres[1] = registers_copy[1];
                registres[2] = registers_copy[2];
                registres[3] = registers_copy[3];
                registres[4] = registers_copy[4];
                registers_copy[0] = 0;
                registers_copy[1] = 0;
                registers_copy[2] = 0;
                registers_copy[3] = 0;
                registers_copy[4] = 0;
            }
            else if (strcmp(arg1, "b") == 0) {
                registres[0] = registers_copy[0];
                registres[2] = registers_copy[2];
                registres[3] = registers_copy[3];
                registres[4] = registers_copy[4];
                registers_copy[0] = 0;
                registers_copy[1] = 0;
                registers_copy[2] = 0;
                registers_copy[3] = 0;
                registers_copy[4] = 0;
            }
            else if (strcmp(arg1, "c") == 0) {
                registres[0] = registers_copy[0];
                registres[1] = registers_copy[1];
                registres[3] = registers_copy[3];
                registres[4] = registers_copy[4];
                registers_copy[0] = 0;
                registers_copy[1] = 0;
                registers_copy[2] = 0;
                registers_copy[3] = 0;
                registers_copy[4] = 0;
            }
            else if (strcmp(arg1, "d") == 0) {
                registres[0] = registers_copy[0];
                registres[1] = registers_copy[1];
                registres[2] = registers_copy[2];
                registres[4] = registers_copy[4];
                registers_copy[0] = 0;
                registers_copy[1] = 0;
                registers_copy[2] = 0;
                registers_copy[3] = 0;
                registers_copy[4] = 0;
            }
            else if (strcmp(arg1, "e") == 0) {
                registres[0] = registers_copy[0];
                registres[1] = registers_copy[1];
                registres[2] = registers_copy[2];
                registres[3] = registers_copy[3];
                registers_copy[0] = 0;
                registers_copy[1] = 0;
                registers_copy[2] = 0;
                registers_copy[3] = 0;
                registers_copy[4] = 0;
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
            else {
                int put = atoll(arg1);
                printf("%d\n", put);
            }
        }
        arg1[0] = '\0';
        arg2[0] = '\0';
        arg3[0] = '\0';
        command_name[0] = '\0';
        command[0] = '\0';
    }
    fclose(pfile);
    pfile = NULL;
    return 0;
}