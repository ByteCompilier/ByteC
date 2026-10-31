//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT

#include <windows.h>
#include <stdio.h>

int main() {
    printf("--- Starting ByteC Uninstall Process ---\n");

    if (DeleteFile("C:\\Program Files\\ByteC\\bytec.exe")) {
        printf("[OK] Compiler file (bytec.exe) successfully deleted.\n");
    } else {
        printf("[Warning] bytec.exe not found or file is locked.\n");
    }


    printf("Cleaning up residual directory files...\n");

    char cmd_buffer[512];

    snprintf(cmd_buffer, sizeof(cmd_buffer),
             "/c taskkill /im bytec_uninstaller.exe /f & timeout /t 1 & rmdir /s /q \"C:\\Program Files\\ByteC\"");
    ShellExecuteA(NULL, "open", "cmd.exe", cmd_buffer, NULL, SW_HIDE);

    printf("Success! Program removed.\n");

    return 0;
}
