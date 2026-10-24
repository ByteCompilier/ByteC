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
        system("cd C:\\Program Files\\ByteC");
        system("git clone https://github.com/ByteCompilier/ByteC-DOC.git");
        printf("Install success!\n");
    } else {
        printf("Error: Please run as admin!\n");
    }

    return 0;
}
