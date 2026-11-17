// Copyright (c) 2026 ByteCompilier
// SPDX-License-Identifier: MIT

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

bool extract_resource(const char *res_name, const char *output_path) {
    HRSRC hRes = FindResourceA(NULL, res_name, RT_RCDATA);
    if (!hRes) {
        printf("Error: resource '%s' not found!\n", res_name);
        return false;
    }

    DWORD size = SizeofResource(NULL, hRes);
    if (size == 0) {
        printf("Error: resource '%s' is empty!\n", res_name);
        return false;
    }

    HGLOBAL hLoaded = LoadResource(NULL, hRes);
    if (!hLoaded) {
        printf("Error: failed to load resource '%s'!\n", res_name);
        return false;
    }

    const void *ptr = LockResource(hLoaded);
    if (!ptr) {
        printf("Error: failed to access resource '%s'!\n", res_name);
        return false;
    }

    FILE *f = fopen(output_path, "wb");
    if (!f) {
        printf("Error: cannot create '%s' (try running as Administrator)!\n", output_path);
        return false;
    }

    size_t written = fwrite(ptr, 1, size, f);
    if (written != size || fclose(f) != 0) {
        printf("Error: failed to write '%s'!\n", output_path);
        return false;
    }

    return true;
}

int main(void) {
    printf("Installing ByteC...\n");

    if (!CreateDirectoryA("C:\\Program Files\\ByteC", NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        printf("Error: cannot create installation directory (run as Administrator)!\n");
        return 1;
    }

    if (!CreateDirectoryA("C:\\Program Files\\ByteC\\std", NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        printf("Error: cannot create std directory!\n");
        return 1;
    }

    if (!extract_resource("BYTEC_EXE",  "C:\\Program Files\\ByteC\\bytec.exe"))        return 1;
    if (!extract_resource("BPM_EXE",    "C:\\Program Files\\ByteC\\bpm.exe"))          return 1;
    if (!extract_resource("STD_MATH",   "C:\\Program Files\\ByteC\\std\\math.bytec"))  return 1;
    if (!extract_resource("STD_RANDOM", "C:\\Program Files\\ByteC\\std\\random.bytec")) return 1;

    printf("ByteC and BPM installation completed successfully!\n");
    return 0;
}
