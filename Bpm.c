// Copyright (c) 2026 ByteCompilier
// SPDX-License-Identifier: MIT


#include <stdbool.h>
#include <stdio.h>
#include <urlmon.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <wininet.h>
#include <pthread.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc >= 3 && strcmp(argv[1], "install") == 0) {
        printf("\n");
        printf("Downloading metafiles!\n");
        char url[1024] = "";
        int result_t = snprintf(url, sizeof(url), "%s", argv[2]);
        if (result_t < 0 || (size_t) result_t >= sizeof(url)) {
            printf("Parse error!\n");
            return 1;
        }
        for (int i = 0; url[i] != '\0'; i++) {
            if (url[i] == '&' || url[i] == '\"' || url[i] == '|' || url[i] == ';' || url[i] == '/' || url[i] == '\\' ||
                url[i] == '.' || url[i] == '%' || url[i] == '<' || url[i] == '>' || url[i] == '(' || url[i] == ')' ||
                url[i] == '^' || url[i] == '!') {
                printf("Unknown symbol '%c'!\n", url[i]);
                return 1;
            }
        }
        char repo[1024] = "https://raw.githubusercontent.com/bytecompilier/BPM-registry/main/";
        char final[1024] = "";
        int result_s = snprintf(final, sizeof(final), "%s%s", repo, url);
        if (result_s < 0 || (size_t) result_s >= sizeof(final)) {
            printf("Parse error!\n");
            return 1;
        }
        DeleteUrlCacheEntryA(final);
        HRESULT result = URLDownloadToFileA(NULL, final, "url", 0, NULL);
        if (result == E_ABORT) {
            printf("Download aborted!\n");
            remove("url");
            return 1;
        } else if (result == E_OUTOFMEMORY) {
            printf("Download out of memory!\n");
            remove("url");
            return 1;
        } else if (result == E_ACCESSDENIED) {
            printf("Download denied!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_NO_SESSION) {
            printf("Failed to open internet session!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_CANNOT_CONNECT) {
            printf("Failed to connect to internet server!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_RESOURCE_NOT_FOUND) {
            printf("Package not found!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_OBJECT_NOT_FOUND) {
            printf("Package not found!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_DATA_NOT_AVAILABLE) {
            printf("Package not available!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_DOWNLOAD_FAILURE) {
            printf("Download failed!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_CONNECTION_TIMEOUT) {
            printf("Connection timeout!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_CANNOT_INSTANTIATE_OBJECT) {
            printf("Cannot instantiate object!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_REDIRECT_FAILED) {
            printf("Redirect failed!\n");
            remove("url");
            return 1;
        } else if (result == INET_E_SECURITY_PROBLEM) {
            printf("Security problem!\n");
            remove("url");
            return 1;
        } else if (FAILED(result)) {
            printf("Code error: 0x%08lX\n", result);
            remove("url");
            return 1;
        }
        FILE *fp = fopen("url", "r");
        if (fp == NULL) {
            printf("Error opening file\n");
            remove("url");
            return 1;
        }
        printf("Downloading packages!\n");
        char url2[1024] = "";
        if (fgets(url2, sizeof(url2), fp) == NULL) {
            printf("Error reading pkg!");
            fclose(fp);
            remove("url");
            return 1;
        }
        fclose(fp);
        url2[strcspn(url2, "\r\n")] = 0;
        if (url2[0] == '\0') {
            printf("Empty URL in metafile!\n");
            remove("url");
            return 1;
        }
        char to[1024] = "";
        char dir[1024] = "libs\\";
        snprintf(to, sizeof(to), "%s%s", dir, url);
        char del_cmd[1024] = "";
        snprintf(del_cmd, sizeof(del_cmd), "rmdir /s /q \"%s\" 2>nul", to);
        system(del_cmd);
        system("mkdir libs 2>nul");
        char made_dir[1024] = "";
        char nul[1024] = "2>nul";
        char com[1024] = "mkdir \".\\libs\\";
        snprintf(made_dir, sizeof(made_dir), "%s%s\" %s", com, url, nul);
        system(made_dir);
        DeleteUrlCacheEntryA(url2);
        HRESULT result_a = URLDownloadToFileA(NULL, url2, "main.zip", 0, NULL);
        if (result_a == E_ABORT) {
            printf("Download aborted!\n");
            remove("url");
            return 1;
        } else if (result_a == E_OUTOFMEMORY) {
            printf("Download out of memory!\n");
            remove("url");
            return 1;
        } else if (result_a == E_ACCESSDENIED) {
            printf("Download denied!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_NO_SESSION) {
            printf("Failed to open internet session!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_CANNOT_CONNECT) {
            printf("Failed to connect to internet server!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_RESOURCE_NOT_FOUND) {
            printf("Package not found!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_OBJECT_NOT_FOUND) {
            printf("Package not found!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_DATA_NOT_AVAILABLE) {
            printf("Package not available!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_DOWNLOAD_FAILURE) {
            printf("Download failed!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_CONNECTION_TIMEOUT) {
            printf("Connection timeout!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_CANNOT_INSTANTIATE_OBJECT) {
            printf("Cannot instantiate object!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_REDIRECT_FAILED) {
            printf("Redirect failed!\n");
            remove("url");
            return 1;
        } else if (result_a == INET_E_SECURITY_PROBLEM) {
            printf("Security problem!\n");
            remove("url");
            return 1;
        } else if (FAILED(result_a)) {
            printf("Code error: 0x%08lX\n", result_a);
            remove("url");
            return 1;
        }
        printf("Unpacking packages!\n");
        char array[1024] = "";
        char comm[1024] = "tar -xf main.zip --strip-components=1 -C \".\\libs\\";
        snprintf(array, sizeof(array), "%s%s\"", comm, url);
        int tar_res = system(array);
        if (tar_res != 0) {
            printf("Package unpacking failed!\n");
            remove("url");
            remove("main.zip");
            return 1;
        }
        printf("Removing metafiles!\n");
        remove("main.zip");
        remove("url");
        printf("Package successfully downloaded!\n");
        return 0;
    } else if (argc >= 3 && strcmp(argv[1], "remove") == 0) {
        bool test = true;
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-y") == 0) {
                test = false;
            }
        }
        char name[1024] = "";
        int result = snprintf(name, sizeof(name), "%s", argv[2]);
        if (result < 0 || (size_t) result >= sizeof(name)) {
            printf("Parse error!\n");
            return 1;
        }
        for (int i = 0; name[i] != '\0'; i++) {
            if (name[i] == '&' || name[i] == '\"' || name[i] == '|' || name[i] == ';' || name[i] == '/' || name[i] ==
                '\\' || name[i] == '.' || name[i] == '%' || name[i] == '<' || name[i] == '>' || name[i] == '(' || name[
                    i] == ')' || name[i] == '^' || name[i] == '!') {
                printf("Unknown symbol '%c'!\n", name[i]);
                return 1;
            }
        }
        if (test) {
            char symbol = '\0';
            printf("Are you sure you want to remove package %s [y\\N]", name);
            scanf(" %c", &symbol);
            if (symbol != 'Y' && symbol != 'y') {
                return 1;
            }
        }
        char remove_pkg[1024] = "";
        char dir[1024] = "rmdir /s /q \"libs\\";
        char nul[1024] = "2>nul";
        int result_t = snprintf(remove_pkg, sizeof(remove_pkg), "%s%s\" %s", dir, name, nul);
        if (result_t < 0 || (size_t) result_t >= sizeof(remove_pkg)) {
            printf("Parse error!\n");
            return 1;
        }
        int result_s = system(remove_pkg);
        if (result_s == -1) {
            printf("Cmd cannot be executed!\n");
            return 1;
        } else if (result_s != 0) {
            printf("Package remove failed!\n");
            return 1;
        }
        printf("Package successfully removed!\n");
        return 0;
    }
}
