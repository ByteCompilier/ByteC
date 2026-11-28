//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT


#include <stdio.h>//include stdio.h library
#include <string.h> // include string.h library
#include <stdint.h>
#include <stdlib.h> //include stdint.h library
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stddef.h>
#include <dirent.h>

#include "../../third_party/iniparser/iniparser.h"
#include "../preprocessor/preprocessor.h"
#include "../parser/parser.h"
#include "../../third_party/raylib/raylib.h"

#define COMMAND_SIZE 256 // our one command size
#define COMMAND_NAME 50//our command name
#define ARG1 50//our command first argument
#define ARG2 50//our command second argument
#define ARG3 50
#define STACK_SIZE 10000
#define ARG_SIZE 50

static int ignore_iniparser_errors(const char *format, ...) {
    (void) format;
    return 0;
}

int main(int argc, char *argv[]) {
    iniparser_set_error_callback(ignore_iniparser_errors);
    //main function
    bool preprocess = true;
    bool debug = false;
    int stroke_count = 0;
    long return_stack[STACK_SIZE];
    int stack_pointer = -1;
    const char *array_s;
    char cwd[1024];
    if (argc >= 3 && strcmp(argv[1], "conf") == 0) {
        char conf_file[100] = "";
        strcpy(conf_file, argv[2]);
        dictionary *ini = iniparser_load(conf_file);
        int result = iniparser_getboolean(ini, "preprocess:preprocess_file", -1);
        if (result == -1) {
        } else if (result == 1) {
            preprocess = true;
        } else if (result == 0) {
            preprocess = false;
        }
        int result_t = iniparser_getboolean(ini, "debug:debug", -1);
        if (result_t == -1) {
        } else if (result_t == 1) {
            debug = true;
        } else if (result_t == 0) {
            debug = false;
        }
        const char *array = iniparser_getstring(ini, "preprocess:preprocess_filename", NULL);
        if (array == NULL) {
        }
        int result_s = 0;
        if (preprocess) { result_s = preprocess_file(array); }
        if (result_s == 1) {
            printf("Error");
            return 1;
        }
        array_s = iniparser_getstring(ini, "library:libraries", NULL);
        if (array_s == NULL) {
            return 1;
        }
        char *dup = strdup(array_s);
        char *buffer = strtok((char *) dup, ",");
        char final[1024] = "";
        char buff[1024] = "";
        strcpy(buff, buffer);
        snprintf(final, sizeof(final), "bpm install \"%s\"", buff);
        system(final);
        while (true) {
            buffer = strtok(NULL, ",");
            if (buffer == NULL) {
                return 0;
            }
            char final_s[1024] = "";
            char buff_s[1024] = "";
            strcpy(buff_s, buffer);
            snprintf(final_s, sizeof(final_s), "bpm install \"%s\"", buff_s);
            system(final_s);
        }
        free(dup);
        iniparser_freedict(ini);

        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        printf("Version alpha 10!\n");
        return 0;
    }
    if (strcmp(argv[1], "--debug") == 0 || debug) {
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
        char array[100] = "";
        strcpy(array, argv[2]);
        FILE *pfile = fopen(array, "r");
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
                    printf("ZS: %d", code_if);
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
            } else if (strcmp(command_d, "next") == 0) {
                printf("\n");
                char litter[1000] = "";
                fgets(litter, sizeof(litter), pfile);
                printf("\n\n");
            } else if (strcmp(command_d, "step") == 0) {
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
    char arg4[ARG3];
    Wave wave[1000] = {0};
    Sound sound[1000] = {0};
    int sound_counter = 0;
    int counter = 0;
    bool audio_mod = false;
    int8_t code_if = 0;
    Sound sound_alias[1000] = {0};
    int sound_alias_counter = 0;
    static char modules[STACK_SIZE][1000];
    short modules_size = -1;
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
        parser(command, command_name, arg1, arg2, arg3, arg4);
        stroke_count++;
        for (int i = 0; command_name[i] != '\0'; i++) {
            command_name[i] = toupper(command_name[i]);
        }
        if (!audio_mod) {
            for (int i = 0; i < 10000; i++) {
                if (strcmp(modules[i], "audio") == 0) {
                    audio_mod = true;
                }
            }
        }

        /*                       module (memory)                          */

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
        }

        /*                   Module (random)                     */

        else if (strcmp(command_name, "__SYSCALL__->SETRANDOM") == 0) {
            if (strcmp(arg1, "default") == 0) {
                srand(time(NULL));
            } else {
                unsigned int put = (unsigned int) strtoul(arg1, NULL, 10);
                srand((unsigned int) put);
            }
        } else if (strcmp(command_name, "__SYSCALL__->RANDOM") == 0) {
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
        }

        /*               Module (compare)                  */

        else if (strcmp(command_name, "CMP") == 0) {
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
        }

        /*                Module (labels and jumps)         */

        else if (strcmp(command_name, "JMP") == 0) {
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
        }

        /*            Module (functions)       */

        else if (strcmp(command_name, "CALL") == 0) {
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
        }

        /*           Module (audio)                  */

        else if (strcmp(command_name, "AUDIO_INIT") == 0 && audio_mod) {
            SetTraceLogLevel(LOG_NONE);
            InitAudioDevice();
            SetMasterVolume(1.0f);
            if (!IsAudioDeviceReady()) {
                printf("In line %d Audio initialization failed!\n", stroke_count);
                return 1;
            }
        } else if (strcmp(command_name, "AUDIO_CLOSE") == 0 && audio_mod) {
            CloseAudioDevice();

            if (IsAudioDeviceReady()) {
                printf("In line %d Audio device was not closed!\n", stroke_count);
                return 1;
            }
        } else if (strcmp(command_name, "AUDIO_VOLUME") == 0 && audio_mod) {
            char *endptr;
            float volume = 0.0f;
            if (strcmp(arg1, "a") == 0) {
                volume = (float) registres[0] / 10;
            } else if (strcmp(arg1, "b") == 0) {
                volume = (float) registres[1] / 10;
            } else if (strcmp(arg1, "c") == 0) {
                volume = (float) registres[2] / 10;
            } else if (strcmp(arg1, "d") == 0) {
                volume = (float) registres[3] / 10;
            } else if (strcmp(arg1, "e") == 0) {
                volume = (float) registres[4] / 10;
            } else {
                volume = (float) (strtof(arg1, &endptr)) / 10;
                if (endptr == arg1 || *endptr != '\0' || !isfinite(volume)) {
                    printf("Argument error: %s\n", arg1);
                    return 1;
                }
            }
            if (volume < 0.0f || volume > 1.0f) {
                printf("In line %d Invalid volume!", stroke_count);
                return 1;
            }
            SetMasterVolume(volume);
        } else if (strcmp(command_name, "AUDIO_READY") == 0 && audio_mod) {
            registres[0] = IsAudioDeviceReady() ? 1 : 0;
        } else if (strcmp(command_name, "AUDIO_GET_VOLUME") == 0 && audio_mod) {
            registres[0] = (int64_t) (GetMasterVolume() * 10.0f);
        } else if (strcmp(command_name, "AUDIO_LOAD_WAVE") == 0 && audio_mod) {
            char final[1000] = "";
            snprintf(final, sizeof(final), "%s%s%s", arg1, arg2, arg3);
            if (counter > 999) {
                printf("In line %d Wave overflow!", stroke_count);
                return 1;
            }
            wave[counter] = LoadWave(final);
            if (!IsWaveValid(wave[counter])) {
                printf("In line %d Wave load failed!", stroke_count);
                return 1;
            }
            counter++;
        } else if (strcmp(command_name, "AUDIO_LOAD_SOUND") == 0 && audio_mod) {
            char final[1000] = "";
            snprintf(final, sizeof(final), "%s%s%s", arg1, arg2, arg3);
            if (sound_counter > 999) {
                printf("In line %d Sound overflow!", stroke_count);
                return 1;
            }
            sound[sound_counter] = LoadSound(final);
            if (!IsSoundValid(sound[sound_counter])) {
                printf("In line %d Sound load failed!", stroke_count);
                return 1;
            }
            sound_counter++;
        } else if (strcmp(command_name, "AUDIO_LOAD_SOUND_FROM_WAVE") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999 || index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (sound_counter > 999) {
                printf("In line %d Sound overflow!", stroke_count);
                return 1;
            }
            sound[sound_counter] = LoadSoundFromWave(wave[index]);
            if (!IsSoundValid(sound[sound_counter])) {
                printf("In line %d Sound load failed!", stroke_count);
                return 1;
            }
            sound_counter++;
        } else if (strcmp(command_name, "AUDIO_UNLOAD_SOUND") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= sound_counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            UnloadSound(sound[index]);
            sound[index] = (Sound){0};
            for (int i = index; i < sound_counter - 1; i++) {
                sound[i] = sound[i + 1];
            }
            sound_counter--;
            sound[sound_counter] = (Sound){0};
        } else if (strcmp(command_name, "AUDIO_PLAY_SOUND") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            PlaySound(sound[index]);
            while (IsSoundPlaying(sound[index])) {
            }
        } else if (strcmp(command_name, "AUDIO_UNLOAD_WAVE") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            UnloadWave(wave[index]);
            wave[index] = (Wave){0};
            for (int i = index; i < counter - 1; i++) {
                wave[i] = wave[i + 1];
            }
            counter--;
            wave[counter] = (Wave){0};
        } else if (strcmp(command_name, "AUDIO_LOAD_SOUND_ALIAS") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= sound_counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (sound_alias_counter >= 1000) {
                printf("In line %d Sound alias limit reached!\n", stroke_count);
                return 1;
            }
            sound_alias[sound_alias_counter] = LoadSoundAlias(sound[index]);
            sound_alias_counter++;
        } else if (strcmp(command_name, "AUDIO_UNLOAD_SOUND_ALIAS") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= sound_alias_counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            UnloadSoundAlias(sound_alias[index]);
            sound_alias[index] = (Sound){0};
            for (int i = index; i < sound_alias_counter - 1; i++) {
                sound_alias[i] = sound_alias[i + 1];
            }
            sound_alias_counter--;
            sound_alias[sound_alias_counter] = (Sound){0};
        } else if (strcmp(command_name, "AUDIO_EXPORT_WAVE") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char final[10000] = "";
            snprintf(final, sizeof(final), "%s%s", arg2, arg3);
            bool status = ExportWave(wave[index], final);
            if (!status) {
                printf("In line %d Error cannot export your wave to file!", stroke_count);
                return 1;
            }
        } else if (strcmp(command_name, "AUDIO_EXPORT_WAVE_AS_CODE") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' || index < 0 || index > 999) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            if (index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char final[10000] = "";
            snprintf(final, sizeof(final), "%s%s", arg2, arg3);
            bool status = ExportWaveAsCode(wave[index], final);
            if (!status) {
                printf("In line %d Error cannot export your wave to file!", stroke_count);
                return 1;
            }
        } else if (strcmp(command_name, "AUDIO_STOP_SOUND") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            StopSound(sound[index]);
        } else if (strcmp(command_name, "AUDIO_PAUSE_SOUND") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            PauseSound(sound[index]);
        } else if (strcmp(command_name, "AUDIO_RESUME_SOUND") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            ResumeSound(sound[index]);
        } else if (strcmp(command_name, "AUDIO_IS_SOUND_PLAYING") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            bool result = IsSoundPlaying(sound[index]);
            if (result) {
                registres[0] = 1;
            } else {
                registres[0] = 0;
            }
        } else if (strcmp(command_name, "AUDIO_IS_SOUND_VALID") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            bool result = IsSoundValid(sound[index]);
            if (result) {
                registres[0] = 1;
            } else {
                registres[0] = 0;
            }
        } else if (strcmp(command_name, "AUDIO_IS_WAVE_VALID") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            bool result = IsWaveValid(wave[index]);
            if (result) {
                registres[0] = 1;
            } else {
                registres[0] = 0;
            }
        } else if (strcmp(command_name, "AUDIO_SET_SOUND_VOLUME") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            char *endptr_t;
            float ind = strtof(arg2, &endptr_t);
            if (endptr_t == arg2 || *endptr_t != '\0' || ind < 0.0f || ind > 1.0f || !isfinite(ind)) {
                printf("In line %d Invalid sound volume!", stroke_count);
                return 1;
            }
            SetSoundVolume(sound[index], ind);
        } else if (strcmp(command_name, "AUDIO_SET_SOUND_PITCH") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            char *endptr_t;
            float ind = strtof(arg2, &endptr_t);
            if (endptr_t == arg2 || *endptr_t != '\0' ||
                ind < 0.0f || !isfinite(ind)) {
                printf("In line %d Invalid sound pitch!", stroke_count);
                return 1;
            }
            SetSoundPitch(sound[index], ind);
        } else if (strcmp(command_name, "AUDIO_SET_SOUND_PAN") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= sound_counter) {
                printf("In line %d Invalid sound index!", stroke_count);
                return 1;
            }
            char *endptr_t;
            float ind = strtof(arg2, &endptr_t);
            if (endptr_t == arg2 || *endptr_t != '\0' ||
                ind < -1.0f || ind > 1.0f || !isfinite(ind)) {
                printf("In line %d Invalid sound pan!", stroke_count);
                return 1;
            }
            SetSoundPan(sound[index], ind);
        } else if (strcmp(command_name, "AUDIO_WAVE_CROP") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char *endptr_t;
            int ind = strtol(arg2, &endptr_t, 10);
            if (endptr_t == arg2 || *endptr_t != '\0' || ind < 0 || ind > INT_MAX) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char *ptr;
            int ind_t = strtol(arg3, &ptr, 10);
            if (ptr == arg3 || *ptr != '\0' || ind_t <= ind || ind_t > INT_MAX) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            WaveCrop(&wave[index], ind, ind_t);
        } else if (strcmp(command_name, "AUDIO_WAVE_FORMAT") == 0 && audio_mod) {
            char *endptr;
            int index = strtol(arg1, &endptr, 10);
            if (endptr == arg1 || *endptr != '\0' ||
                index < 0 || index >= counter) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
                }
            char *endptr_t;
            int ind = strtol(arg2, &endptr_t, 10);
            if (endptr_t == arg2 || *endptr_t != '\0' || ind <= 0 || ind > INT_MAX) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char *ptr;
            int ind_t = strtol(arg3, &ptr, 10);
            if (ptr == arg3 || *ptr != '\0' || ind_t > INT_MAX) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            char *ptrt;
            int ind_t_t = strtol(arg4, &ptrt, 10);
            if (ptrt == arg4 || *ptrt != '\0' || ind_t_t > INT_MAX) {
                printf("In line %d Invalid index!", stroke_count);
                return 1;
            }
            WaveFormat(&wave[index], ind, ind_t, ind_t_t);
        } else if (strcmp(command_name, ""))
        /*                      Module (arithmetics operations)                        */

        else if (strcmp(command_name, "ADD") == 0) {
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
        } else if (strcmp(command_name, "DIV") == 0) {
            if (arg1[0] == 'a') {
                if (arg2[0] == 'a') {
                    if (registres[0] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[0] /= registres[0];
                } else if (arg2[0] == 'b') {
                    if (registres[1] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[0] /= registres[1];
                } else if (arg2[0] == 'c') {
                    if (registres[2] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[0] /= registres[2];
                } else if (arg2[0] == 'd') {
                    if (registres[3] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[0] /= registres[3];
                } else if (arg2[0] == 'e') {
                    if (registres[4] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[0] /= registres[4];
                } else if (arg2[0] == '\0') {
                    printf("In line %d\n", stroke_count);
                    exit(1);
                } else {
                    int64_t test = strtoll(arg2, NULL, 10);
                    if (test == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    int put = atoi(arg2);
                    registres[0] /= put;
                }
            } else if (arg1[0] == 'b') {
                if (arg2[0] == 'a') {
                    if (registres[0] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[1] /= registres[0];
                } else if (arg2[0] == 'b') {
                    if (registres[1] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[1] /= registres[1];
                } else if (arg2[0] == 'c') {
                    if (registres[2] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[1] /= registres[2];
                } else if (arg2[0] == 'd') {
                    if (registres[3] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[1] /= registres[3];
                } else if (arg2[0] == 'e') {
                    if (registres[4] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[1] /= registres[4];
                } else {
                    int64_t test = strtoll(arg2, NULL, 10);
                    if (test == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    int put = atoi(arg2);
                    registres[1] /= put;
                }
            } else if (arg1[0] == 'c') {
                if (arg2[0] == 'a') {
                    if (registres[0] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[2] /= registres[0];
                } else if (arg2[0] == 'b') {
                    if (registres[1] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[2] /= registres[1];
                } else if (arg2[0] == 'c') {
                    if (registres[2] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[2] /= registres[2];
                } else if (arg2[0] == 'd') {
                    if (registres[3] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[2] /= registres[3];
                } else if (arg2[0] == 'e') {
                    if (registres[4] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[2] /= registres[4];
                } else {
                    int64_t test = strtoll(arg2, NULL, 10);
                    if (test == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    int put = atoi(arg2);
                    registres[2] /= put;
                }
            } else if (arg1[0] == 'd') {
                if (arg2[0] == 'a') {
                    if (registres[0] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[3] /= registres[0];
                } else if (arg2[0] == 'b') {
                    if (registres[1] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[3] /= registres[1];
                } else if (arg2[0] == 'c') {
                    if (registres[2] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[3] /= registres[2];
                } else if (arg2[0] == 'd') {
                    if (registres[3] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[3] /= registres[3];
                } else if (arg2[0] == 'e') {
                    if (registres[4] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[3] /= registres[4];
                } else {
                    int64_t test = strtoll(arg2, NULL, 10);
                    if (test == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    int put = atoi(arg2);
                    registres[3] /= put;
                }
            } else if (arg1[0] == 'e') {
                if (arg2[0] == 'a') {
                    if (registres[0] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[4] /= registres[0];
                } else if (arg2[0] == 'b') {
                    if (registres[1] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[4] /= registres[1];
                } else if (arg2[0] == 'c') {
                    if (registres[2] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[4] /= registres[2];
                } else if (arg2[0] == 'd') {
                    if (registres[3] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[4] /= registres[3];
                } else if (arg2[0] == 'e') {
                    if (registres[4] == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
                    registres[4] /= registres[4];
                } else {
                    int64_t test = strtoll(arg2, NULL, 10);
                    if (test == 0) {
                        printf("In line %d division by zero!\n", stroke_count);
                        exit(1);
                    }
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
        }

        /*           Module (I/O)           */

        else if (strcmp(command_name, "IN") == 0) {
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
            } else if (strcmp(arg1, "ZS") == 0) {
                int8_t put = (int8_t) code_if;
                printf("%d\n", (int8_t) put);
            } else {
                int64_t put = (long long) atoll(arg1);
                printf("%lld\n", (long long) put);
            }
        }

        /*         Module (Modules)         */

        else if (strcmp(command_name, "MODULE") == 0) {
            modules_size++;
            strcpy(modules[modules_size], arg1);
        }

        /*             Ignore commands            */

        else if (strcmp(command_name, "\n") == 0 || strcmp(command_name, " ") == 0 || strcmp(command_name, "") == 0 ||
                 strcmp(command_name, ":") == 0 || strcmp(command_name, ";") == 0 || strcmp(command_name, "INCLUDE") ==
                 0) {
        }

        /*             Unknown instructions       */

        else {
            printf("In line %d unknown instruction %s!", stroke_count, command_name);
            exit(1);
        }

        /*                Clearing buffers          */

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
