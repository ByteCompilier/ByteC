//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT

#include <windows.h>
#include <stdio.h>

int main() {
    CreateDirectory("C:\\Program Files\\ByteC", NULL);

    HRSRC hRes = FindResource(NULL, "BYTEC_EXE", RT_RCDATA);
    if (!hRes) {
        printf("Error resource not found: bytec.c\n");
        return 1;
    }

    HGLOBAL hLog = LoadResource(NULL, hRes);
    DWORD size = SizeofResource(NULL, hRes);
    void* ptr = LockResource(hLog);

    FILE* f = fopen("C:\\Program Files\\ByteC\\bytec.exe", "wb");
    if (f) {
        fwrite(ptr, 1, size, f);
        fclose(f);
        system("cd C:\\Program Files\\ByteC && git clone -b DOC --single-branch https://github.com/ByteCompilier/ByteC.git && rmdir /s /q C:\\Program Files\\ByteC\\DOC\\.git");
        printf("Install success!\n");
    } else {
        printf("Error: Please run as admin!\n");
    }

    return 0;
}
