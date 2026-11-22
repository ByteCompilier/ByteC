#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preprocess_file(const char *input) {
    FILE *fp = fopen(input, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char file_prep[10000] = "";
    char buffer_k[10000] = "";
    char buffer[256] = "";
    char command[256];
    char arg1[256];
    char arg2[256];
    char arg3[256];
    FILE *fp_lib = fopen("prep.bc", "w+");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        sscanf(buffer, "%s %s %s %s", command, arg1, arg2, arg3);
        if (strcmp(command, "INCLUDE") == 0) {
            if (fp_lib == NULL) {
                printf("Error opening file\n");
                return 1;
            }
            FILE *fp2 = fopen(arg1, "r");
            if (fp2 == NULL) {
                printf("Error opening file\n");
                return 1;
            }
            while (fgets(buffer_k, sizeof(buffer_k), fp2) != NULL) {
                fputs(buffer_k, fp_lib);
            }
            fclose(fp2);
        }
        arg1[0] = '\0';
        arg2[0] = '\0';
        arg3[0] = '\0';
        command[0] = '\0';
        buffer[0] = '\0';
        buffer_k[0] = '\0';
    }
    rewind(fp);

    while (fgets(file_prep, sizeof(file_prep), fp) != NULL) {
        fputs(file_prep, fp_lib);
        file_prep[0] = '\0';
    }
    fclose(fp_lib);
    fclose(fp);
    return 0;
}
