//Copyright (c) 2026 ByteCompilier
//SPDX-License-Identifier: MIT

#include <windows.h>
#include <stdio.h>

int main(void) {
    HRSRC hRes = FindResourceA(NULL, "BYTEC_EXE", RT_RCDATA);
    HRSRC hRes_math = FindResourceA(NULL, "STD_MATH", RT_RCDATA);
    HRSRC hRes_random = FindResourceA(NULL, "STD_RANDOM", RT_RCDATA);

    if (!hRes || !hRes_math || !hRes_random) {
        printf("Error: resource not found!\n");
        return 1;
    }

    DWORD size = SizeofResource(NULL, hRes);
    DWORD size_math = SizeofResource(NULL, hRes_math);
    DWORD size_random = SizeofResource(NULL, hRes_random);

    if (!size || !size_math || !size_random) {
        printf("Error: empty resource!\n");
        return 1;
    }

    HGLOBAL hLog = LoadResource(NULL, hRes);
    HGLOBAL hLog_math = LoadResource(NULL, hRes_math);
    HGLOBAL hLog_random = LoadResource(NULL, hRes_random);

    if (!hLog || !hLog_math || !hLog_random) {
        printf("Error: failed to load resources!\n");
        return 1;
    }

    const void* ptr = LockResource(hLog);
    const void* ptr_math = LockResource(hLog_math);
    const void* ptr_random = LockResource(hLog_random);

    if (!ptr || !ptr_math || !ptr_random) {
        printf("Error: failed to access resources!\n");
        return 1;
    }

    if (!CreateDirectoryA("C:\\Program Files\\ByteC", NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        printf("Error: cannot create installation directory!\n");
        return 1;
    }

    if (!CreateDirectoryA("C:\\Program Files\\ByteC\\std", NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        printf("Error: cannot create std directory!\n");
        return 1;
    }

    FILE* f = fopen("C:\\Program Files\\ByteC\\bytec.exe", "wb");
    if (!f) {
        printf("Error: cannot create bytec.exe!\n");
        return 1;
    }

    if (fwrite(ptr, 1, size, f) != size || fclose(f) != 0) {
        printf("Error: failed to write bytec.exe!\n");
        return 1;
    }

    FILE* pfile = fopen("C:\\Program Files\\ByteC\\std\\math.bytec", "wb");
    if (!pfile) {
        printf("Error: cannot create math.bytec!\n");
        return 1;
    }

    if (fwrite(ptr_math, 1, size_math, pfile) != size_math || fclose(pfile) != 0) {
        printf("Error: failed to write math.bytec!\n");
        return 1;
    }

    FILE* rfile = fopen("C:\\Program Files\\ByteC\\std\\random.bytec", "wb");
    if (!rfile) {
        printf("Error: cannot create random.bytec!\n");
        return 1;
    }

    if (fwrite(ptr_random, 1, size_random, rfile) != size_random || fclose(rfile) != 0) {
        printf("Error: failed to write random.bytec!\n");
        return 1;
    }

    printf("ByteC installation completed successfully!\n");

    return 0;
}
