/*
 * Copyright (C) 2026  Daniel Shirvanyan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://gnu.org>.
 */
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
    char command[COMMAND_SIZE]; // our command buffer
    char command_name[COMMAND_SIZE];//our command name var
    char arg1[ARG1];
    char arg2[ARG2];
    int8_t registres[5];
    FILE *pfile = fopen(argv[1], "r");//opens file in read mode
    if(pfile == NULL) {//if file dont opened we return 1
        printf("Error opening file\n");//printing error
        return 1;
    }
    //if file opened successfully
    while (!feof(pfile)) {//our main cycle
        fgets(command, COMMAND_SIZE, pfile);// input one command for testing
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
        else if (strcmp(command_name, "PR") == 0) {
            int integer = atoi(arg1);
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
