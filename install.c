//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT

#include <windows.h>
#include <stdio.h>

int main() {
    CreateDirectory("C:\\Program Files\\ByteC", NULL);

    HRSRC hRes = FindResource(NULL, "BYTEC_EXE", RT_RCDATA);
    HRSRC hRes_math = FindResource(NULL, "STD_MATH", RT_RCDATA);
    if (!hRes_math) {
        printf("Error resource not found: math.bytec\n");
    }
    if (!hRes) {
        printf("Error resource not found: bytec.c\n");
        return 1;
    }

    HGLOBAL hLog = LoadResource(NULL, hRes);
    DWORD size = SizeofResource(NULL, hRes);
    void* ptr = LockResource(hLog);


    HGLOBAL hLog_math = LoadResource(NULL, hRes_math);
    DWORD size_math = SizeofResource(NULL, hRes_math);
    void* ptr_ter = LockResource(hLog_math);

    FILE* f = fopen("C:\\Program Files\\ByteC\\bytec.exe", "wb");
    if (f) {
        fwrite(ptr, 1, size, f);
        fclose(f);
        system("cd C:\\Program Files\\ByteC");
        printf("Install success!\n");
    } else {
        printf("Error: Please run as admin!\n");
    }
    system("mkdir \"C:\\Program Files\\ByteC\\std\"");
    system("cd C:\\Program Files\\ByteC\\std\\");
    FILE *pfile = fopen("C:\\Program Files\\ByteC\\std\\math.bytec", "w");
    if (pfile) {
        fprintf(pfile, "%s", ptr_ter);
        fclose(pfile);
        system("cd C:\\Program Files\\ByteC\\");
        printf("Install success!\n");
    }

    return 0;
}
