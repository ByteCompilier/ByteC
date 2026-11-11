//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT


#include <stdio.h>//include stdio.h library
#include <string.h> // include string.h library
#include <stdint.h>
#include <stdlib.h> //include stdint.h library
#include <time.h>
#include <stdbool.h>

#include "preprocessor.h"


#define COMMAND_SIZE 256 // our one command size
#define COMMAND_NAME 50//our command name
#define ARG1 50//our command first argument
#define ARG2 50//our command second argument
#define ARG3 50
#define STACK_SIZE 10000
#define ARG_SIZE 50

int main(int argc, char *argv[]) {
    //main function
    int stroke_count = 0;
    long return_stack[STACK_SIZE];
    int stack_pointer = -1;

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        printf("Version alpha 6!\n");
        return 0;
    }
    if (strcmp(argv[1], "--debug") == 0) {
        bool preprocessed = false;
        printf("ByteC Debugger v0.1\n");
        printf("\n");
        printf("Loaded: %s", argv[2]);
        char buffer[COMMAND_SIZE] = "";
        char command_d[COMMAND_NAME];
        char arg1_d[ARG_SIZE];
        int64_t register_stack[STACK_SIZE][5];
        int64_t arguments[STACK_SIZE][2];
        char command[COMMAND_SIZE]; // our command buffer
        char command_name[COMMAND_SIZE]; //our command name var
        char arg1[ARG1];
        char arg2[ARG2];
        char arg3[ARG3];
        if (preprocess_file(argv[2]) != 0) {
            printf("Preprocessor error!\n");
            return 1;
        }
        int8_t code_if = 0;
        int64_t registres[5] = {0};
        printf("\n\n");
        FILE *pfile = fopen("prep.bc", "r");
        if (pfile == NULL) {
            printf("Error opening file\n");
        }
        while (1) {
            printf("(bytec-debug)");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%49s %49s", command_d, arg1_d);
            if (strcmp(command_d, "quit") == 0) {
                printf("\n");
                fclose(pfile);
                exit(0);
            } else if (strcmp(command_d, "help") == 0) {
                printf("\n");
                printf("Available commands:\n");
                printf("  help  - Show commands\n");
                printf("  quit  - Exit debugger\n"
                       "  regs  - Print registers values\n"
                       "  step  - Do one command\n"
                       "  list  - Print programs code\n"
                       "  next  - Not do one command but skip it\n");
                printf("\n");
            } else if (strcmp(command_d, "regs") == 0) {
                printf("\n");
                if (preprocessed) {
                    for (int i = 0; i < 5; i++) {
                        if (i == 0) {
                            printf("Register a: ");
                        } else if (i == 1) {
                            printf("Register b: ");
                        } else if (i == 2) {
                            printf("Register c: ");
                        } else if (i == 3) {
                            printf("Register d: ");
                        } else if (i == 4) {
                            printf("Register e: ");
                        }
                        printf("%lld\n", registres[i]);
                    }
                } else {
                    if (preprocess_file(argv[2]) != 0) {
                        printf("Preprocessor error!\n");
                        return 1;
                    }
                    preprocessed = true;
                    for (int i = 0; i < 5; i++) {
                        if (i == 0) {
                            printf("Register a: ");
                        } else if (i == 1) {
                            printf("Register b: ");
                        } else if (i == 2) {
                            printf("Register c: ");
                        } else if (i == 3) {
                            printf("Register d: ");
                        } else if (i == 4) {
                            printf("Register e: ");
                        }
                        printf("%lld\n", registres[i]);
                    }
                }
                printf("\n");
            } else if (strcmp(command_d, "list") == 0) {
                printf("\n");
                printf("File %s code\n\n", argv[2]);
                char time_buff[COMMAND_SIZE] = "";
                while (fgets(time_buff, sizeof(time_buff), pfile) != NULL) {
                    printf("%s", time_buff);
                    time_buff[0] = '\0';
                }
                fseek(pfile, 0, SEEK_SET);
                printf("\n\n");
            }
            else if (strcmp(command_d, "next") ==0) {
                printf("\n");
                char litter[1000] ="";
                fgets(litter, sizeof(litter), pfile);
                printf("\n\n");
            }

            else if (strcmp(command_d, "step") == 0) {
                bool hello = false;
                printf("\n");
                if (preprocessed) {
                    while (!hello) {
                        fgets(command, sizeof(command), pfile);
                        hello = true;
                        // input one command for testing
                        sscanf(command, "%s %s %s %s", command_name, arg1, arg2, arg3);
                        stroke_count++;
                        if (strcmp(command_name, "MOV") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[0] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[0] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[0] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[0] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[0] = registres[4];
                                } else {
                                    registres[0] = put;
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[1] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[1] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[1] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[1] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[1] = registres[4];
                                } else {
                                    registres[1] = put;
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[2] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[2] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[2] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[2] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[2] = registres[4];
                                } else {
                                    registres[2] = put;
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[3] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[3] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[3] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[3] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[3] = registres[4];
                                } else {
                                    registres[3] = put;
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[4] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[4] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[4] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[4] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[4] = registres[4];
                                } else {
                                    registres[4] = put;
                                }
                            } else {
                                printf(
                                    "In line %d Syntax Error: You can only move a number or another register into a register.\n",
                                    stroke_count);
                                _Exit(1);
                            }
                        } else if (strcmp(command_name, "__syscall__->SETRANDOM") == 0) {
                            if (strcmp(arg1, "default") == 0) {
                                srand(time(NULL));
                            } else {
                                unsigned int put = (unsigned int) strtoul(arg1, NULL, 10);
                                srand((unsigned int) put);
                            }
                        } else if (strcmp(command_name, "__syscall__->RANDOM") == 0) {
                            int64_t put_t = 0;
                            int64_t put = 0;
                            if (strcmp(arg1, "a") == 0) {
                                put = registres[0];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);

                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                put = registres[1];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456788 = atoll(arg2);

                                    put_t = put123456788;
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                put = registres[2];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                put = registres[3];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                put = registres[4];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else {
                                int64_t put123456789 = atoll(arg1);
                                put = put123456789;
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            }

                            if (put <= 0) {
                                printf("In line %d ERROR: First argument must be natural number!\n", stroke_count);
                                _Exit(1);
                            }
                            if (put_t > put) {
                                printf("In line %d ERROR: Invalid random range!\n", stroke_count);
                                _Exit(1);
                            }
                            int64_t res = rand() % (put - put_t + 1) + put_t;
                            registres[0] = res;
                        } else if (strcmp(command_name, "CMP") == 0) {
                            if (strcmp(arg2, "==") == 0) {
                                if (strcmp(arg1, "a") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[0] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[0] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[0] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[0] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[0] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[0] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "b") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[1] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[1] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[1] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[1] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[1] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[1] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "c") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[2] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[2] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[2] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[2] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[2] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[2] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "d") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[3] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[3] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[3] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[3] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[3] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[3] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "e") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[4] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[4] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[4] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[4] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[4] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[4] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
                                    int64_t put = (long long) strtoll(arg3, NULL, 10);
                                    if (strcmp(arg3, "a") == 0) {
                                        if (put == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (put == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (put == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (put == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (put == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put_r = (long long) strtoll(arg3, NULL, 10);
                                        if (put == put_r) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                }
                            } else if (strcmp(arg2, "<") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, ">") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, ">=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, "<=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, "!=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                        } else if (strcmp(command_name, "JIF") == 0) {
                            if (code_if == 0) {
                                rewind(pfile);
                                while (1) {
                                    int x = '\0';
                                    while (x != ':') {
                                        x = fgetc(pfile);
                                        if (x == EOF) {
                                            goto exit_d;
                                        }
                                    }
                                    fseek(pfile, 1, SEEK_CUR);
                                    for (int i = 0; 1 == 1; i++) {
                                        char proverka[100];
                                        char *status = 0;
                                        status = fgets(proverka, sizeof(proverka), pfile);
                                        proverka[strcspn(proverka, "\r\n")] = '\0';
                                        if (status == NULL) {
                                            goto exit_d;
                                        }
                                        if (strcmp(proverka, arg1) == 0) {
                                            goto exit_d;
                                        } else {
                                            break;
                                        }
                                    }
                                }
                            exit_d:;
                            }
                        } else if (strcmp(command_name, "JIT") == 0) {
                            if (code_if == 1) {
                                rewind(pfile);
                                while (1) {
                                    int x = '\0';
                                    while (x != ':') {
                                        x = fgetc(pfile);
                                        if (x == EOF) {
                                            goto hu_d;
                                        }
                                    }
                                    fseek(pfile, 1, SEEK_CUR);
                                    for (int i = 0; 1 == 1; i++) {
                                        char proverka[100];
                                        char *status = 0;
                                        status = fgets(proverka, sizeof(proverka), pfile);
                                        proverka[strcspn(proverka, "\r\n")] = '\0';
                                        if (status == NULL) {
                                            goto hu_d;
                                        }
                                        if (strcmp(proverka, arg1) == 0) {
                                            goto hu_d;
                                        } else {
                                            break;
                                        }
                                    }
                                }
                            hu_d:;
                            }
                        } else if (strcmp(command_name, "JMP") == 0) {
                            rewind(pfile);
                            while (1) {
                                int x = '\0';
                                while (x != ':') {
                                    x = fgetc(pfile);
                                    if (x == EOF) {
                                        goto label_d;
                                    }
                                }
                                fseek(pfile, 1, SEEK_CUR);
                                for (int i = 0; 1 == 1; i++) {
                                    char proverka[100];
                                    char *status = 0;
                                    status = fgets(proverka, sizeof(proverka), pfile);
                                    if (status == NULL) {
                                        goto label_d;
                                    }
                                    proverka[strcspn(proverka, "\r\n")] = '\0';
                                    if (strcmp(proverka, arg1) == 0) {
                                        goto label_d;
                                    } else {
                                        break;
                                    }
                                }
                            }
                        label_d:;
                        } else if (strcmp(command_name, "CALL") == 0) {
                            stack_pointer++;
                            return_stack[stack_pointer] = ftell(pfile);
                            if (strcmp(arg2, "a") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "b") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "c") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "d") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "e") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put_tr = atoll(arg3);
                                    arguments[stack_pointer][1] = put_tr;
                                }
                                long long put = atoll(arg2);
                                arguments[stack_pointer][0] = put;
                            }
                            for (int i = 0; i < 5; i++) {
                                register_stack[stack_pointer][i] = registres[i];
                            }
                            for (int i = 0; i < 5; i++) {
                                registres[i] = 0;
                            }
                            rewind(pfile);
                            while (1) {
                                int x = '\0';
                                while (x != ':') {
                                    x = fgetc(pfile);
                                    if (x == EOF) {
                                        goto labelk_d;
                                    }
                                }
                                fseek(pfile, 1, SEEK_CUR);
                                for (int i = 0; 1 == 1; i++) {
                                    char proverka[100];
                                    char *status = 0;
                                    status = fgets(proverka, sizeof(proverka), pfile);

                                    if (status == NULL) {
                                        printf("CALL: label not found: %s\n", arg1);
                                        stack_pointer--;
                                        fseek(pfile, return_stack[stack_pointer + 1], SEEK_SET);
                                        goto labelk_d;
                                    }

                                    proverka[strcspn(proverka, "\r\n")] = '\0';
                                    if (strcmp(proverka, arg1) == 0) {
                                        goto labelk_d;
                                    } else {
                                        break;
                                    }
                                }
                            }
                        labelk_d:;
                        } else if (strcmp(command_name, "ADD") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] += put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] += put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] += put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] += put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] += put;
                                }
                            }
                        } else if (strcmp(command_name, "MUL") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] *= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] *= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] *= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] *= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] *= put;
                                }
                            }
                        } else if (strcmp(command_name, "INCLUDE") == 0) {
                        } else if (strcmp(command_name, "SUB") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] -= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] -= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] -= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] -= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] -= put;
                                }
                            }
                        } else if (strcmp(command_name, "ARG") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[0] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[0] = arguments[stack_pointer][1];
                                } else {
                                    printf("In line %d ERROR please write 1 or 2!\n", stack_pointer);
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[1] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[1] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[2] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[2] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[3] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[3] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[4] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[4] = arguments[stack_pointer][1];
                                }
                            } else {
                                printf("In line %d register not found!\n", stack_pointer);
                            }
                        } else if (strcmp(command_name, "DIV") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] /= registres[4];
                                } else if (arg2[0] == '\0') {
                                    printf("In line %d\n", stroke_count);
                                    system("\"C:\\program files\\bytec\\bytec\\ERROR3.bat\"");
                                    exit(1);
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] /= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] /= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] /= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] /= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] /= put;
                                }
                            }
                        } else if (strcmp(command_name, "NEG") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] = registres[0] - (registres[0] * 2);
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] = registres[1] - (registres[1] * 2);
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] = registres[2] - (registres[2] * 2);
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] = registres[3] - (registres[3] * 2);
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] = registres[4] - (registres[4] * 2);
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "INC") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] += 1;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] += 1;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] += 1;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] += 1;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] += 1;
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "DEC") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] -= 1;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] -= 1;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] -= 1;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] -= 1;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] -= 1;
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "IN") == 0) {
                            int64_t number = 0;
                            scanf("%lld", &number);
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] = number;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] = number;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] = number;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] = number;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] = number;
                            } else {
                                printf("Register not found\n");
                            }
                        } else if (strcmp(command_name, ";") == 0) {
                            continue;
                        } else if (strcmp(command_name, "RET") == 0) {
                            if (stack_pointer < 0 || stack_pointer >= 10000) {
                                printf("VM error: invalid stack_pointer: %d\n", stack_pointer);
                                return 1;
                            }
                            int return_register = -1;

                            if (strcmp(arg1, "a") == 0) return_register = 0;
                            else if (strcmp(arg1, "b") == 0) return_register = 1;
                            else if (strcmp(arg1, "c") == 0) return_register = 2;
                            else if (strcmp(arg1, "d") == 0) return_register = 3;
                            else if (strcmp(arg1, "e") == 0) return_register = 4;
                            long long value = registres[return_register];
                            for (int i = 0; i < 5; i++) {
                                registres[i] = register_stack[stack_pointer][i];
                            }
                            registres[return_register] = value;
                            fseek(pfile, return_stack[stack_pointer], SEEK_SET);
                            return_stack[stack_pointer] = 0;
                            for (int i = 0; i < 5; i++) {
                                register_stack[stack_pointer][i] = 0;
                            }
                            for (int i = 0; i < 2; i++) {
                                arguments[stack_pointer][i] = 0;
                            }
                            stack_pointer--;
                        } else if (strcmp(command_name, "PR") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                int64_t put = (long long) registres[0];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "b") == 0) {
                                int64_t put = (long long) registres[1];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "c") == 0) {
                                int64_t put = (long long) registres[2];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "d") == 0) {
                                int64_t put = (long long) registres[3];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "e") == 0) {
                                int64_t put = (long long) registres[4];
                                printf("%lld\n", (long long) put);
                            } else {
                                int64_t put = (long long) atoll(arg1);
                                printf("%lld\n", (long long) put);
                            }
                        }
                        arg1[0] = '\0';
                        arg2[0] = '\0';
                        arg3[0] = '\0';
                        command_name[0] = '\0';
                        command[0] = '\0';
                    }
                } else {
                    bool hello = false;
                    if (preprocess_file(argv[2]) != 0) {
                        printf("Preprocessor error!\n");
                        return 1;
                    }
                    preprocessed = true;
                    while (!hello) {
                        // input one command for testing
                        fgets(command, sizeof(command), pfile);
                        hello = true;
                        sscanf(command, "%s %s %s %s", command_name, arg1, arg2, arg3);
                        stroke_count++;
                        if (strcmp(command_name, "MOV") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[0] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[0] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[0] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[0] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[0] = registres[4];
                                } else {
                                    registres[0] = put;
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[1] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[1] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[1] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[1] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[1] = registres[4];
                                } else {
                                    registres[1] = put;
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[2] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[2] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[2] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[2] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[2] = registres[4];
                                } else {
                                    registres[2] = put;
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[3] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[3] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[3] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[3] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[3] = registres[4];
                                } else {
                                    registres[3] = put;
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                int64_t put = atoll(arg2);
                                if (strcmp(arg2, "a") == 0) {
                                    registres[4] = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    registres[4] = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    registres[4] = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    registres[4] = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    registres[4] = registres[4];
                                } else {
                                    registres[4] = put;
                                }
                            } else {
                                printf(
                                    "In line %d Syntax Error: You can only move a number or another register into a register.\n",
                                    stroke_count);
                                _Exit(1);
                            }
                        } else if (strcmp(command_name, "__syscall__->SETRANDOM") == 0) {
                            if (strcmp(arg1, "default") == 0) {
                                srand(time(NULL));
                            } else {
                                unsigned int put = (unsigned int) strtoul(arg1, NULL, 10);
                                srand((unsigned int) put);
                            }
                        } else if (strcmp(command_name, "__syscall__->RANDOM") == 0) {
                            int64_t put_t = 0;
                            int64_t put = 0;
                            if (strcmp(arg1, "a") == 0) {
                                put = registres[0];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);

                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                put = registres[1];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456788 = atoll(arg2);

                                    put_t = put123456788;
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                put = registres[2];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                put = registres[3];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                put = registres[4];
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            } else {
                                int64_t put123456789 = atoll(arg1);
                                put = put123456789;
                                if (strcmp(arg2, "a") == 0) {
                                    put_t = registres[0];
                                } else if (strcmp(arg2, "b") == 0) {
                                    put_t = registres[1];
                                } else if (strcmp(arg2, "c") == 0) {
                                    put_t = registres[2];
                                } else if (strcmp(arg2, "d") == 0) {
                                    put_t = registres[3];
                                } else if (strcmp(arg2, "e") == 0) {
                                    put_t = registres[4];
                                } else {
                                    int64_t put123456789 = atoll(arg2);
                                    put_t = put123456789;
                                }
                            }

                            if (put <= 0) {
                                printf("In line %d ERROR: First argument must be natural number!\n", stroke_count);
                                _Exit(1);
                            }
                            if (put_t > put) {
                                printf("In line %d ERROR: Invalid random range!\n", stroke_count);
                                _Exit(1);
                            }
                            int64_t res = rand() % (put - put_t + 1) + put_t;
                            registres[0] = res;
                        } else if (strcmp(command_name, "CMP") == 0) {
                            if (strcmp(arg2, "==") == 0) {
                                if (strcmp(arg1, "a") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[0] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[0] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[0] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[0] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[0] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[0] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "b") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[1] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[1] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[1] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[1] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[1] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[1] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "c") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[2] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[2] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[2] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[2] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[2] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[2] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "d") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[3] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[3] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[3] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[3] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[3] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[3] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (strcmp(arg1, "e") == 0) {
                                    if (strcmp(arg3, "a") == 0) {
                                        if (registres[4] == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (registres[4] == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (registres[4] == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (registres[4] == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (registres[4] == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                                        if (registres[4] == put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
                                    int64_t put = (long long) strtoll(arg3, NULL, 10);
                                    if (strcmp(arg3, "a") == 0) {
                                        if (put == registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "b") == 0) {
                                        if (put == registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "c") == 0) {
                                        if (put == registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "d") == 0) {
                                        if (put == registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (strcmp(arg3, "e") == 0) {
                                        if (put == registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int64_t put_r = (long long) strtoll(arg3, NULL, 10);
                                        if (put == put_r) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                }
                            } else if (strcmp(arg2, "<") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] < registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] < registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] < registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] < registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] < registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] < put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, ">") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] > registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] > registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] > registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] > registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] > registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] > put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, ">=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] >= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] >= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] >= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] >= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] >= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] >= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, "<=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] <= registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] <= registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] <= registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] <= registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] <= registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] <= put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                            } else if (strcmp(arg2, "!=") == 0) {
                                if (arg1[0] == 'a') {
                                    if (arg3[0] == 'a') {
                                        if (registres[0] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[0] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[0] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[0] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[0] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[0] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'b') {
                                    if (arg3[0] == 'a') {
                                        if (registres[1] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[1] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[1] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[1] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[1] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[1] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'c') {
                                    if (arg3[0] == 'a') {
                                        if (registres[2] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[2] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[2] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[2] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[2] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[2] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'd') {
                                    if (arg3[0] == 'a') {
                                        if (registres[3] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[3] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[3] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[3] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[3] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[3] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else if (arg1[0] == 'e') {
                                    if (arg3[0] == 'a') {
                                        if (registres[4] != registres[0]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'b') {
                                        if (registres[4] != registres[1]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'c') {
                                        if (registres[4] != registres[2]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'd') {
                                        if (registres[4] != registres[3]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else if (arg3[0] == 'e') {
                                        if (registres[4] != registres[4]) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    } else {
                                        int put = atoll(arg3);
                                        if (registres[4] != put) {
                                            code_if = 1;
                                        } else {
                                            code_if = 0;
                                        }
                                    }
                                } else {
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
                        } else if (strcmp(command_name, "JIF") == 0) {
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
                                    for (int i = 0; 1 == 1; i++) {
                                        char proverka[100];
                                        char *status = 0;
                                        status = fgets(proverka, sizeof(proverka), pfile);
                                        proverka[strcspn(proverka, "\r\n")] = '\0';
                                        if (status == NULL) {
                                            goto exit;
                                        }
                                        if (strcmp(proverka, arg1) == 0) {
                                            goto exit;
                                        } else {
                                            break;
                                        }
                                    }
                                }
                            exit:;
                            }
                        } else if (strcmp(command_name, "JIT") == 0) {
                            if (code_if == 1) {
                                rewind(pfile);
                                while (1) {
                                    int x = '\0';
                                    while (x != ':') {
                                        x = fgetc(pfile);
                                        if (x == EOF) {
                                            goto hu_d;
                                        }
                                    }
                                    fseek(pfile, 1, SEEK_CUR);
                                    for (int i = 0; 1 == 1; i++) {
                                        char proverka[100];
                                        char *status = 0;
                                        status = fgets(proverka, sizeof(proverka), pfile);
                                        proverka[strcspn(proverka, "\r\n")] = '\0';
                                        if (status == NULL) {
                                            goto hu;
                                        }
                                        if (strcmp(proverka, arg1) == 0) {
                                            goto hu;
                                        } else {
                                            break;
                                        }
                                    }
                                }
                            hu:;
                            }
                        } else if (strcmp(command_name, "JMP") == 0) {
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
                                for (int i = 0; 1 == 1; i++) {
                                    char proverka[100];
                                    char *status = 0;
                                    status = fgets(proverka, sizeof(proverka), pfile);
                                    if (status == NULL) {
                                        goto label;
                                    }
                                    proverka[strcspn(proverka, "\r\n")] = '\0';
                                    if (strcmp(proverka, arg1) == 0) {
                                        goto label;
                                    } else {
                                        break;
                                    }
                                }
                            }
                        label:;
                        } else if (strcmp(command_name, "CALL") == 0) {
                            stack_pointer++;
                            return_stack[stack_pointer] = ftell(pfile);
                            if (strcmp(arg2, "a") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[0];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "b") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[1];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "c") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[2];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "d") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[3];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else if (strcmp(arg2, "e") == 0) {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][0] = registres[4];
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put = atoll(arg2);
                                    int put_r = atoll(arg3);
                                    arguments[stack_pointer][0] = put;
                                    arguments[stack_pointer][1] = put_r;
                                }
                            } else {
                                if (strcmp(arg3, "a") == 0) {
                                    arguments[stack_pointer][1] = registres[0];
                                } else if (strcmp(arg3, "b") == 0) {
                                    arguments[stack_pointer][1] = registres[1];
                                } else if (strcmp(arg3, "c") == 0) {
                                    arguments[stack_pointer][1] = registres[2];
                                } else if (strcmp(arg3, "d") == 0) {
                                    arguments[stack_pointer][1] = registres[3];
                                } else if (strcmp(arg3, "e") == 0) {
                                    arguments[stack_pointer][1] = registres[4];
                                } else {
                                    long long put_tr = atoll(arg3);
                                    arguments[stack_pointer][1] = put_tr;
                                }
                                long long put = atoll(arg2);
                                arguments[stack_pointer][0] = put;
                            }
                            for (int i = 0; i < 5; i++) {
                                register_stack[stack_pointer][i] = registres[i];
                            }
                            for (int i = 0; i < 5; i++) {
                                registres[i] = 0;
                            }
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
                                for (int i = 0; 1 == 1; i++) {
                                    char proverka[100];
                                    char *status = 0;
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
                                    } else {
                                        break;
                                    }
                                }
                            }
                        labelk:;
                        } else if (strcmp(command_name, "ADD") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] += put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] += put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] += put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] += put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] += registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] += registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] += registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] += registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] += registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] += put;
                                }
                            }
                        } else if (strcmp(command_name, "MUL") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] *= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] *= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] *= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] *= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] *= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] *= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] *= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] *= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] *= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] *= put;
                                }
                            }
                        } else if (strcmp(command_name, "INCLUDE") == 0) {
                        } else if (strcmp(command_name, "SUB") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] -= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] -= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] -= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] -= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] -= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] -= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] -= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] -= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] -= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] -= put;
                                }
                            }
                        } else if (strcmp(command_name, "ARG") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[0] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[0] = arguments[stack_pointer][1];
                                } else {
                                    printf("In line %d ERROR please write 1 or 2!\n", stack_pointer);
                                }
                            } else if (strcmp(arg1, "b") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[1] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[1] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "c") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[2] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[2] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "d") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[3] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[3] = arguments[stack_pointer][1];
                                }
                            } else if (strcmp(arg1, "e") == 0) {
                                if (strcmp(arg2, "1") == 0) {
                                    registres[4] = arguments[stack_pointer][0];
                                } else if (strcmp(arg2, "2") == 0) {
                                    registres[4] = arguments[stack_pointer][1];
                                }
                            } else {
                                printf("In line %d register not found!\n", stack_pointer);
                            }
                        } else if (strcmp(command_name, "DIV") == 0) {
                            if (arg1[0] == 'a') {
                                if (arg2[0] == 'a') {
                                    registres[0] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[0] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[0] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[0] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[0] /= registres[4];
                                } else if (arg2[0] == '\0') {
                                    printf("In line %d\n", stroke_count);
                                    system("\"C:\\program files\\bytec\\bytec\\ERROR3.bat\"");
                                    exit(1);
                                } else {
                                    int put = atoi(arg2);
                                    registres[0] /= put;
                                }
                            } else if (arg1[0] == 'b') {
                                if (arg2[0] == 'a') {
                                    registres[1] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[1] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[1] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[1] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[1] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[1] /= put;
                                }
                            } else if (arg1[0] == 'c') {
                                if (arg2[0] == 'a') {
                                    registres[2] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[2] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[2] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[2] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[2] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[2] /= put;
                                }
                            } else if (arg1[0] == 'd') {
                                if (arg2[0] == 'a') {
                                    registres[3] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[3] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[3] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[3] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[3] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[3] /= put;
                                }
                            } else if (arg1[0] == 'e') {
                                if (arg2[0] == 'a') {
                                    registres[4] /= registres[0];
                                } else if (arg2[0] == 'b') {
                                    registres[4] /= registres[1];
                                } else if (arg2[0] == 'c') {
                                    registres[4] /= registres[2];
                                } else if (arg2[0] == 'd') {
                                    registres[4] /= registres[3];
                                } else if (arg2[0] == 'e') {
                                    registres[4] /= registres[4];
                                } else {
                                    int put = atoi(arg2);
                                    registres[4] /= put;
                                }
                            }
                        } else if (strcmp(command_name, "NEG") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] = registres[0] - (registres[0] * 2);
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] = registres[1] - (registres[1] * 2);
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] = registres[2] - (registres[2] * 2);
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] = registres[3] - (registres[3] * 2);
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] = registres[4] - (registres[4] * 2);
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "INC") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] += 1;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] += 1;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] += 1;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] += 1;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] += 1;
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "DEC") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] -= 1;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] -= 1;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] -= 1;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] -= 1;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] -= 1;
                            } else {
                                printf("Register not found\n");
                                exit(1);
                            }
                        } else if (strcmp(command_name, "IN") == 0) {
                            int64_t number = 0;
                            scanf("%lld", &number);
                            if (strcmp(arg1, "a") == 0) {
                                registres[0] = number;
                            } else if (strcmp(arg1, "b") == 0) {
                                registres[1] = number;
                            } else if (strcmp(arg1, "c") == 0) {
                                registres[2] = number;
                            } else if (strcmp(arg1, "d") == 0) {
                                registres[3] = number;
                            } else if (strcmp(arg1, "e") == 0) {
                                registres[4] = number;
                            } else {
                                printf("Register not found\n");
                            }
                        } else if (strcmp(command_name, ";") == 0) {
                            continue;
                        } else if (strcmp(command_name, "RET") == 0) {
                            if (stack_pointer < 0 || stack_pointer >= 10000) {
                                printf("VM error: invalid stack_pointer: %d\n", stack_pointer);
                                return 1;
                            }
                            int return_register = -1;

                            if (strcmp(arg1, "a") == 0) return_register = 0;
                            else if (strcmp(arg1, "b") == 0) return_register = 1;
                            else if (strcmp(arg1, "c") == 0) return_register = 2;
                            else if (strcmp(arg1, "d") == 0) return_register = 3;
                            else if (strcmp(arg1, "e") == 0) return_register = 4;
                            long long value = registres[return_register];
                            for (int i = 0; i < 5; i++) {
                                registres[i] = register_stack[stack_pointer][i];
                            }
                            registres[return_register] = value;
                            fseek(pfile, return_stack[stack_pointer], SEEK_SET);
                            return_stack[stack_pointer] = 0;
                            for (int i = 0; i < 5; i++) {
                                register_stack[stack_pointer][i] = 0;
                            }
                            for (int i = 0; i < 2; i++) {
                                arguments[stack_pointer][i] = 0;
                            }
                            stack_pointer--;
                        } else if (strcmp(command_name, "PR") == 0) {
                            if (strcmp(arg1, "a") == 0) {
                                int64_t put = (long long) registres[0];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "b") == 0) {
                                int64_t put = (long long) registres[1];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "c") == 0) {
                                int64_t put = (long long) registres[2];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "d") == 0) {
                                int64_t put = (long long) registres[3];
                                printf("%lld\n", (long long) put);
                            } else if (strcmp(arg1, "e") == 0) {
                                int64_t put = (long long) registres[4];
                                printf("%lld\n", (long long) put);
                            } else {
                                int64_t put = (long long) atoll(arg1);
                                printf("%lld\n", (long long) put);
                            }
                        }
                        arg1[0] = '\0';
                        arg2[0] = '\0';
                        arg3[0] = '\0';
                        command_name[0] = '\0';
                        command[0] = '\0';
                    }
                }
            } else if (strcmp(command_d, "") == 0) {
                printf("\n");
            } else {
                printf("\n");
                printf("Unknown command: %s\n", command_d);
                printf("\n");
            }
            command_d[0] = '\0';
            arg1_d[0] = '\0';
            buffer[0] = '\0';
        }
    }
    if (argc < 2) {
        printf("Command line args error!\n");
        return 1;
    }

    if (preprocess_file(argv[1]) != 0) {
        printf("Preprocessor error!\n");
        return 1;
    }

    int64_t register_stack[STACK_SIZE][5];
    int64_t arguments[STACK_SIZE][2];
    char command[COMMAND_SIZE]; // our command buffer
    char command_name[COMMAND_SIZE]; //our command name var
    char arg1[ARG1];
    char arg2[ARG2];
    char arg3[ARG3];
    int8_t code_if = 0;
    int64_t registres[5] = {0};
    FILE *pfile = fopen("prep.bc", "r"); //opens file in read mode
    if (pfile == NULL) {
        //if file dont opened we return 1
        printf("Error opening file\n"); //printing error
        return 1;
    }
    //if file opened successfully
    while (fgets(command, COMMAND_SIZE, pfile) != NULL) {
        // input one command for testing
        sscanf(command, "%s %s %s %s", command_name, arg1, arg2, arg3);
        stroke_count++;
        if (strcmp(command_name, "MOV") == 0) {
            if (strcmp(arg1, "a") == 0) {
                int64_t put = atoll(arg2);
                if (strcmp(arg2, "a") == 0) {
                    registres[0] = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    registres[0] = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    registres[0] = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    registres[0] = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    registres[0] = registres[4];
                } else {
                    registres[0] = put;
                }
            } else if (strcmp(arg1, "b") == 0) {
                int64_t put = atoll(arg2);
                if (strcmp(arg2, "a") == 0) {
                    registres[1] = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    registres[1] = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    registres[1] = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    registres[1] = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    registres[1] = registres[4];
                } else {
                    registres[1] = put;
                }
            } else if (strcmp(arg1, "c") == 0) {
                int64_t put = atoll(arg2);
                if (strcmp(arg2, "a") == 0) {
                    registres[2] = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    registres[2] = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    registres[2] = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    registres[2] = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    registres[2] = registres[4];
                } else {
                    registres[2] = put;
                }
            } else if (strcmp(arg1, "d") == 0) {
                int64_t put = atoll(arg2);
                if (strcmp(arg2, "a") == 0) {
                    registres[3] = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    registres[3] = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    registres[3] = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    registres[3] = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    registres[3] = registres[4];
                } else {
                    registres[3] = put;
                }
            } else if (strcmp(arg1, "e") == 0) {
                int64_t put = atoll(arg2);
                if (strcmp(arg2, "a") == 0) {
                    registres[4] = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    registres[4] = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    registres[4] = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    registres[4] = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    registres[4] = registres[4];
                } else {
                    registres[4] = put;
                }
            } else {
                printf("In line %d Syntax Error: You can only move a number or another register into a register.\n",
                       stroke_count);
                _Exit(1);
            }
        } else if (strcmp(command_name, "__syscall__->SETRANDOM") == 0) {
            if (strcmp(arg1, "default") == 0) {
                srand(time(NULL));
            } else {
                unsigned int put = (unsigned int) strtoul(arg1, NULL, 10);
                srand((unsigned int) put);
            }
        } else if (strcmp(command_name, "__syscall__->RANDOM") == 0) {
            int64_t put_t = 0;
            int64_t put = 0;
            if (strcmp(arg1, "a") == 0) {
                put = registres[0];
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456789 = atoll(arg2);

                    put_t = put123456789;
                }
            } else if (strcmp(arg1, "b") == 0) {
                put = registres[1];
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456788 = atoll(arg2);

                    put_t = put123456788;
                }
            } else if (strcmp(arg1, "c") == 0) {
                put = registres[2];
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456789 = atoll(arg2);
                    put_t = put123456789;
                }
            } else if (strcmp(arg1, "d") == 0) {
                put = registres[3];
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456789 = atoll(arg2);
                    put_t = put123456789;
                }
            } else if (strcmp(arg1, "e") == 0) {
                put = registres[4];
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456789 = atoll(arg2);
                    put_t = put123456789;
                }
            } else {
                int64_t put123456789 = atoll(arg1);
                put = put123456789;
                if (strcmp(arg2, "a") == 0) {
                    put_t = registres[0];
                } else if (strcmp(arg2, "b") == 0) {
                    put_t = registres[1];
                } else if (strcmp(arg2, "c") == 0) {
                    put_t = registres[2];
                } else if (strcmp(arg2, "d") == 0) {
                    put_t = registres[3];
                } else if (strcmp(arg2, "e") == 0) {
                    put_t = registres[4];
                } else {
                    int64_t put123456789 = atoll(arg2);
                    put_t = put123456789;
                }
            }

            if (put <= 0) {
                printf("In line %d ERROR: First argument must be natural number!\n", stroke_count);
                _Exit(1);
            }
            if (put_t > put) {
                printf("In line %d ERROR: Invalid random range!\n", stroke_count);
                _Exit(1);
            }
            int64_t res = rand() % (put - put_t + 1) + put_t;
            registres[0] = res;
        } else if (strcmp(command_name, "CMP") == 0) {
            if (strcmp(arg2, "==") == 0) {
                if (strcmp(arg1, "a") == 0) {
                    if (strcmp(arg3, "a") == 0) {
                        if (registres[0] == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (registres[0] == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (registres[0] == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (registres[0] == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (registres[0] == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                        if (registres[0] == put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (strcmp(arg1, "b") == 0) {
                    if (strcmp(arg3, "a") == 0) {
                        if (registres[1] == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (registres[1] == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (registres[1] == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (registres[1] == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (registres[1] == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                        if (registres[1] == put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (strcmp(arg1, "c") == 0) {
                    if (strcmp(arg3, "a") == 0) {
                        if (registres[2] == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (registres[2] == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (registres[2] == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (registres[2] == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (registres[2] == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                        if (registres[2] == put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (strcmp(arg1, "d") == 0) {
                    if (strcmp(arg3, "a") == 0) {
                        if (registres[3] == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (registres[3] == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (registres[3] == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (registres[3] == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (registres[3] == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                        if (registres[3] == put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (strcmp(arg1, "e") == 0) {
                    if (strcmp(arg3, "a") == 0) {
                        if (registres[4] == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (registres[4] == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (registres[4] == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (registres[4] == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (registres[4] == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put = (long long) strtoll(arg3, NULL, 10);
                        if (registres[4] == put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
                    int64_t put = (long long) strtoll(arg3, NULL, 10);
                    if (strcmp(arg3, "a") == 0) {
                        if (put == registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "b") == 0) {
                        if (put == registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "c") == 0) {
                        if (put == registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "d") == 0) {
                        if (put == registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (strcmp(arg3, "e") == 0) {
                        if (put == registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int64_t put_r = (long long) strtoll(arg3, NULL, 10);
                        if (put == put_r) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                }
            } else if (strcmp(arg2, "<") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[0] < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[0] < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[0] < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[0] < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[0] < put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[1] < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[1] < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[1] < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[1] < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[1] < put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[2] < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[2] < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[2] < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[2] < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[2] < put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[3] < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[3] < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[3] < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[3] < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[3] < put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] < registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[4] < registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[4] < registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[4] < registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[4] < registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[4] < put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
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
            } else if (strcmp(arg2, ">") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[0] > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[0] > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[0] > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[0] > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[0] > put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[1] > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[1] > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[1] > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[1] > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[1] > put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[2] > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[2] > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[2] > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[2] > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[2] > put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[3] > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[3] > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[3] > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[3] > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[3] > put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] > registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[4] > registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[4] > registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[4] > registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[4] > registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[4] > put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
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
            } else if (strcmp(arg2, ">=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[0] >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[0] >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[0] >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[0] >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[0] >= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[1] >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[1] >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[1] >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[1] >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[1] >= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[2] >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[2] >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[2] >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[2] >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[2] >= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[3] >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[3] >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[3] >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[3] >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[3] >= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] >= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[4] >= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[4] >= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[4] >= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[4] >= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[4] >= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
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
            } else if (strcmp(arg2, "<=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[0] <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[0] <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[0] <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[0] <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[0] <= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[1] <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[1] <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[1] <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[1] <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[1] <= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[2] <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[2] <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[2] <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[2] <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[2] <= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[3] <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[3] <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[3] <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[3] <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[3] <= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] <= registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[4] <= registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[4] <= registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[4] <= registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[4] <= registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[4] <= put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
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
            } else if (strcmp(arg2, "!=") == 0) {
                if (arg1[0] == 'a') {
                    if (arg3[0] == 'a') {
                        if (registres[0] != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[0] != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[0] != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[0] != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[0] != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[0] != put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'b') {
                    if (arg3[0] == 'a') {
                        if (registres[1] != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[1] != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[1] != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[1] != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[1] != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[1] != put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'c') {
                    if (arg3[0] == 'a') {
                        if (registres[2] != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[2] != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[2] != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[2] != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[2] != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[2] != put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'd') {
                    if (arg3[0] == 'a') {
                        if (registres[3] != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[3] != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[3] != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[3] != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[3] != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[3] != put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else if (arg1[0] == 'e') {
                    if (arg3[0] == 'a') {
                        if (registres[4] != registres[0]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'b') {
                        if (registres[4] != registres[1]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'c') {
                        if (registres[4] != registres[2]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'd') {
                        if (registres[4] != registres[3]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else if (arg3[0] == 'e') {
                        if (registres[4] != registres[4]) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    } else {
                        int put = atoll(arg3);
                        if (registres[4] != put) {
                            code_if = 1;
                        } else {
                            code_if = 0;
                        }
                    }
                } else {
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
        } else if (strcmp(command_name, "JIF") == 0) {
            if (code_if == 0) {
                rewind(pfile);
                while (1) {
                    int x = '\0';
                    while (x != ':') {
                        x = fgetc(pfile);
                        if (x == EOF) {
                            goto exitg;
                        }
                    }
                    fseek(pfile, 1, SEEK_CUR);
                    for (int i = 0; 1 == 1; i++) {
                        char proverka[100];
                        char *status = 0;
                        status = fgets(proverka, sizeof(proverka), pfile);
                        proverka[strcspn(proverka, "\r\n")] = '\0';
                        if (status == NULL) {
                            goto exitg;
                        }
                        if (strcmp(proverka, arg1) == 0) {
                            goto exitg;
                        } else {
                            break;
                        }
                    }
                }
            exitg:;
            }
        } else if (strcmp(command_name, "JIT") == 0) {
            if (code_if == 1) {
                rewind(pfile);
                while (1) {
                    int x = '\0';
                    while (x != ':') {
                        x = fgetc(pfile);
                        if (x == EOF) {
                            goto hug;
                        }
                    }
                    fseek(pfile, 1, SEEK_CUR);
                    for (int i = 0; 1 == 1; i++) {
                        char proverka[100];
                        char *status = 0;
                        status = fgets(proverka, sizeof(proverka), pfile);
                        proverka[strcspn(proverka, "\r\n")] = '\0';
                        if (status == NULL) {
                            goto hug;
                        }
                        if (strcmp(proverka, arg1) == 0) {
                            goto hug;
                        } else {
                            break;
                        }
                    }
                }
            hug:;
            }
        } else if (strcmp(command_name, "JMP") == 0) {
            rewind(pfile);
            while (1) {
                int x = '\0';
                while (x != ':') {
                    x = fgetc(pfile);
                    if (x == EOF) {
                        goto labelh;
                    }
                }
                fseek(pfile, 1, SEEK_CUR);
                for (int i = 0; 1 == 1; i++) {
                    char proverka[100];
                    char *status = 0;
                    status = fgets(proverka, sizeof(proverka), pfile);
                    if (status == NULL) {
                        goto labelh;
                    }
                    proverka[strcspn(proverka, "\r\n")] = '\0';
                    if (strcmp(proverka, arg1) == 0) {
                        goto labelh;
                    } else {
                        break;
                    }
                }
            }
        labelh:;
        } else if (strcmp(command_name, "CALL") == 0) {
            stack_pointer++;
            return_stack[stack_pointer] = ftell(pfile);
            if (strcmp(arg2, "a") == 0) {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][0] = registres[0];
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][0] = registres[0];
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][0] = registres[0];
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][0] = registres[0];
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][0] = registres[0];
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put = atoll(arg2);
                    int put_r = atoll(arg3);
                    arguments[stack_pointer][0] = put;
                    arguments[stack_pointer][1] = put_r;
                }
            } else if (strcmp(arg2, "b") == 0) {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][0] = registres[1];
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][0] = registres[1];
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][0] = registres[1];
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][0] = registres[1];
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][0] = registres[1];
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put = atoll(arg2);
                    int put_r = atoll(arg3);
                    arguments[stack_pointer][0] = put;
                    arguments[stack_pointer][1] = put_r;
                }
            } else if (strcmp(arg2, "c") == 0) {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][0] = registres[2];
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][0] = registres[2];
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][0] = registres[2];
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][0] = registres[2];
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][0] = registres[2];
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put = atoll(arg2);
                    int put_r = atoll(arg3);
                    arguments[stack_pointer][0] = put;
                    arguments[stack_pointer][1] = put_r;
                }
            } else if (strcmp(arg2, "d") == 0) {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][0] = registres[3];
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][0] = registres[3];
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][0] = registres[3];
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][0] = registres[3];
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][0] = registres[3];
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put = atoll(arg2);
                    int put_r = atoll(arg3);
                    arguments[stack_pointer][0] = put;
                    arguments[stack_pointer][1] = put_r;
                }
            } else if (strcmp(arg2, "e") == 0) {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][0] = registres[4];
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][0] = registres[4];
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][0] = registres[4];
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][0] = registres[4];
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][0] = registres[4];
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put = atoll(arg2);
                    int put_r = atoll(arg3);
                    arguments[stack_pointer][0] = put;
                    arguments[stack_pointer][1] = put_r;
                }
            } else {
                if (strcmp(arg3, "a") == 0) {
                    arguments[stack_pointer][1] = registres[0];
                } else if (strcmp(arg3, "b") == 0) {
                    arguments[stack_pointer][1] = registres[1];
                } else if (strcmp(arg3, "c") == 0) {
                    arguments[stack_pointer][1] = registres[2];
                } else if (strcmp(arg3, "d") == 0) {
                    arguments[stack_pointer][1] = registres[3];
                } else if (strcmp(arg3, "e") == 0) {
                    arguments[stack_pointer][1] = registres[4];
                } else {
                    long long put_tr = atoll(arg3);
                    arguments[stack_pointer][1] = put_tr;
                }
                long long put = atoll(arg2);
                arguments[stack_pointer][0] = put;
            }
            for (int i = 0; i < 5; i++) {
                register_stack[stack_pointer][i] = registres[i];
            }
            for (int i = 0; i < 5; i++) {
                registres[i] = 0;
            }
            rewind(pfile);
            while (1) {
                int x = '\0';
                while (x != ':') {
                    x = fgetc(pfile);
                    if (x == EOF) {
                        goto labelg;
                    }
                }
                fseek(pfile, 1, SEEK_CUR);
                for (int i = 0; 1 == 1; i++) {
                    char proverka[100];
                    char *status = 0;
                    status = fgets(proverka, sizeof(proverka), pfile);

                    if (status == NULL) {
                        printf("CALL: label not found: %s\n", arg1);
                        stack_pointer--;
                        fseek(pfile, return_stack[stack_pointer + 1], SEEK_SET);
                        goto labelg;
                    }

                    proverka[strcspn(proverka, "\r\n")] = '\0';
                    if (strcmp(proverka, arg1) == 0) {
                        goto labelg;
                    } else {
                        break;
                    }
                }
            }
        labelg:;
        } else if (strcmp(command_name, "ADD") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] += registres[0];
                } else if (arg2[0] == 'b') {
                    registres[0] += registres[1];
                } else if (arg2[0] == 'c') {
                    registres[0] += registres[2];
                } else if (arg2[0] == 'd') {
                    registres[0] += registres[3];
                } else if (arg2[0] == 'e') {
                    registres[0] += registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[0] += put;
                }
            } else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] += registres[0];
                } else if (arg2[0] == 'b') {
                    registres[1] += registres[1];
                } else if (arg2[0] == 'c') {
                    registres[1] += registres[2];
                } else if (arg2[0] == 'd') {
                    registres[1] += registres[3];
                } else if (arg2[0] == 'e') {
                    registres[1] += registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[1] += put;
                }
            } else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] += registres[0];
                } else if (arg2[0] == 'b') {
                    registres[2] += registres[1];
                } else if (arg2[0] == 'c') {
                    registres[2] += registres[2];
                } else if (arg2[0] == 'd') {
                    registres[2] += registres[3];
                } else if (arg2[0] == 'e') {
                    registres[2] += registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[2] += put;
                }
            } else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] += registres[0];
                } else if (arg2[0] == 'b') {
                    registres[3] += registres[1];
                } else if (arg2[0] == 'c') {
                    registres[3] += registres[2];
                } else if (arg2[0] == 'd') {
                    registres[3] += registres[3];
                } else if (arg2[0] == 'e') {
                    registres[3] += registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[3] += put;
                }
            } else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] += registres[0];
                } else if (arg2[0] == 'b') {
                    registres[4] += registres[1];
                } else if (arg2[0] == 'c') {
                    registres[4] += registres[2];
                } else if (arg2[0] == 'd') {
                    registres[4] += registres[3];
                } else if (arg2[0] == 'e') {
                    registres[4] += registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[4] += put;
                }
            }
        } else if (strcmp(command_name, "MUL") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] *= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[0] *= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[0] *= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[0] *= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[0] *= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[0] *= put;
                }
            } else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] *= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[1] *= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[1] *= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[1] *= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[1] *= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[1] *= put;
                }
            } else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] *= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[2] *= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[2] *= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[2] *= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[2] *= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[2] *= put;
                }
            } else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] *= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[3] *= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[3] *= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[3] *= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[3] *= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[3] *= put;
                }
            } else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] *= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[4] *= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[4] *= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[4] *= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[4] *= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[4] *= put;
                }
            }
        } else if (strcmp(command_name, "INCLUDE") == 0) {
        } else if (strcmp(command_name, "SUB") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] -= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[0] -= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[0] -= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[0] -= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[0] -= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[0] -= put;
                }
            } else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] -= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[1] -= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[1] -= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[1] -= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[1] -= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[1] -= put;
                }
            } else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] -= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[2] -= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[2] -= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[2] -= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[2] -= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[2] -= put;
                }
            } else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] -= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[3] -= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[3] -= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[3] -= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[3] -= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[3] -= put;
                }
            } else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] -= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[4] -= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[4] -= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[4] -= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[4] -= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[4] -= put;
                }
            }
        } else if (strcmp(command_name, "ARG") == 0) {
            if (strcmp(arg1, "a") == 0) {
                if (strcmp(arg2, "1") == 0) {
                    registres[0] = arguments[stack_pointer][0];
                } else if (strcmp(arg2, "2") == 0) {
                    registres[0] = arguments[stack_pointer][1];
                } else {
                    printf("In line %d ERROR please write 1 or 2!\n", stack_pointer);
                }
            } else if (strcmp(arg1, "b") == 0) {
                if (strcmp(arg2, "1") == 0) {
                    registres[1] = arguments[stack_pointer][0];
                } else if (strcmp(arg2, "2") == 0) {
                    registres[1] = arguments[stack_pointer][1];
                }
            } else if (strcmp(arg1, "c") == 0) {
                if (strcmp(arg2, "1") == 0) {
                    registres[2] = arguments[stack_pointer][0];
                } else if (strcmp(arg2, "2") == 0) {
                    registres[2] = arguments[stack_pointer][1];
                }
            } else if (strcmp(arg1, "d") == 0) {
                if (strcmp(arg2, "1") == 0) {
                    registres[3] = arguments[stack_pointer][0];
                } else if (strcmp(arg2, "2") == 0) {
                    registres[3] = arguments[stack_pointer][1];
                }
            } else if (strcmp(arg1, "e") == 0) {
                if (strcmp(arg2, "1") == 0) {
                    registres[4] = arguments[stack_pointer][0];
                } else if (strcmp(arg2, "2") == 0) {
                    registres[4] = arguments[stack_pointer][1];
                }
            } else {
                printf("In line %d register not found!\n", stack_pointer);
            }
        } else if (strcmp(command_name, "DIV") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    registres[0] /= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[0] /= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[0] /= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[0] /= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[0] /= registres[4];
                } else if (arg2[0] == '\0') {
                    printf("In line %d\n", stroke_count);
                    system("\"C:\\program files\\bytec\\bytec\\ERROR3.bat\"");
                    exit(1);
                } else {
                    int put = atoi(arg2);
                    registres[0] /= put;
                }
            } else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    registres[1] /= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[1] /= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[1] /= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[1] /= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[1] /= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[1] /= put;
                }
            } else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    registres[2] /= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[2] /= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[2] /= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[2] /= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[2] /= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[2] /= put;
                }
            } else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    registres[3] /= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[3] /= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[3] /= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[3] /= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[3] /= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[3] /= put;
                }
            } else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    registres[4] /= registres[0];
                } else if (arg2[0] == 'b') {
                    registres[4] /= registres[1];
                } else if (arg2[0] == 'c') {
                    registres[4] /= registres[2];
                } else if (arg2[0] == 'd') {
                    registres[4] /= registres[3];
                } else if (arg2[0] == 'e') {
                    registres[4] /= registres[4];
                } else {
                    int put = atoi(arg2);
                    registres[4] /= put;
                }
            }
        } else if (strcmp(command_name, "NEG") == 0) {
            if (strcmp(arg1, "a") == 0) {
                registres[0] = registres[0] - (registres[0] * 2);
            } else if (strcmp(arg1, "b") == 0) {
                registres[1] = registres[1] - (registres[1] * 2);
            } else if (strcmp(arg1, "c") == 0) {
                registres[2] = registres[2] - (registres[2] * 2);
            } else if (strcmp(arg1, "d") == 0) {
                registres[3] = registres[3] - (registres[3] * 2);
            } else if (strcmp(arg1, "e") == 0) {
                registres[4] = registres[4] - (registres[4] * 2);
            } else {
                printf("Register not found\n");
                exit(1);
            }
        } else if (strcmp(command_name, "INC") == 0) {
            if (strcmp(arg1, "a") == 0) {
                registres[0] += 1;
            } else if (strcmp(arg1, "b") == 0) {
                registres[1] += 1;
            } else if (strcmp(arg1, "c") == 0) {
                registres[2] += 1;
            } else if (strcmp(arg1, "d") == 0) {
                registres[3] += 1;
            } else if (strcmp(arg1, "e") == 0) {
                registres[4] += 1;
            } else {
                printf("Register not found\n");
                exit(1);
            }
        } else if (strcmp(command_name, "DEC") == 0) {
            if (strcmp(arg1, "a") == 0) {
                registres[0] -= 1;
            } else if (strcmp(arg1, "b") == 0) {
                registres[1] -= 1;
            } else if (strcmp(arg1, "c") == 0) {
                registres[2] -= 1;
            } else if (strcmp(arg1, "d") == 0) {
                registres[3] -= 1;
            } else if (strcmp(arg1, "e") == 0) {
                registres[4] -= 1;
            } else {
                printf("Register not found\n");
                exit(1);
            }
        } else if (strcmp(command_name, "IN") == 0) {
            int64_t number = 0;
            scanf("%lld", &number);
            if (strcmp(arg1, "a") == 0) {
                registres[0] = number;
            } else if (strcmp(arg1, "b") == 0) {
                registres[1] = number;
            } else if (strcmp(arg1, "c") == 0) {
                registres[2] = number;
            } else if (strcmp(arg1, "d") == 0) {
                registres[3] = number;
            } else if (strcmp(arg1, "e") == 0) {
                registres[4] = number;
            } else {
                printf("Register not found\n");
            }
        } else if (strcmp(command_name, ";") == 0) {
            continue;
        } else if (strcmp(command_name, "RET") == 0) {
            if (stack_pointer < 0 || stack_pointer >= 10000) {
                printf("VM error: invalid stack_pointer: %d\n", stack_pointer);
                return 1;
            }
            int return_register = -1;

            if (strcmp(arg1, "a") == 0) return_register = 0;
            else if (strcmp(arg1, "b") == 0) return_register = 1;
            else if (strcmp(arg1, "c") == 0) return_register = 2;
            else if (strcmp(arg1, "d") == 0) return_register = 3;
            else if (strcmp(arg1, "e") == 0) return_register = 4;
            long long value = registres[return_register];
            for (int i = 0; i < 5; i++) {
                registres[i] = register_stack[stack_pointer][i];
            }
            registres[return_register] = value;
            fseek(pfile, return_stack[stack_pointer], SEEK_SET);
            return_stack[stack_pointer] = 0;
            for (int i = 0; i < 5; i++) {
                register_stack[stack_pointer][i] = 0;
            }
            for (int i = 0; i < 2; i++) {
                arguments[stack_pointer][i] = 0;
            }
            stack_pointer--;
        } else if (strcmp(command_name, "PR") == 0) {
            if (strcmp(arg1, "a") == 0) {
                int64_t put = (long long) registres[0];
                printf("%lld\n", (long long) put);
            } else if (strcmp(arg1, "b") == 0) {
                int64_t put = (long long) registres[1];
                printf("%lld\n", (long long) put);
            } else if (strcmp(arg1, "c") == 0) {
                int64_t put = (long long) registres[2];
                printf("%lld\n", (long long) put);
            } else if (strcmp(arg1, "d") == 0) {
                int64_t put = (long long) registres[3];
                printf("%lld\n", (long long) put);
            } else if (strcmp(arg1, "e") == 0) {
                int64_t put = (long long) registres[4];
                printf("%lld\n", (long long) put);
            } else {
                int64_t put = (long long) atoll(arg1);
                printf("%lld\n", (long long) put);
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
