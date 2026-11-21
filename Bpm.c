// Copyright (c) 2026 ByteCompilier
// SPDX-License-Identifier: MIT


#include <stdbool.h>
#include <stdio.h>
#include <urlmon.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <stdarg.h>
#include <wininet.h>
#include <stdint.h>
#include "iniparser.h"

static int ignore_iniparser_errors(const char *format, ...) {
    (void)format;
    return 0;
}


int main(int argc, char *argv[]) {
    iniparser_set_error_callback(ignore_iniparser_errors);
    if (argc >= 3 && strcmp(argv[1], "install") == 0) {
        for (int arg_i = 2; arg_i < argc; arg_i++) {
            printf("\n");
            printf("Downloading metafiles!\n");
            char url[1024] = "";
            int result_t = snprintf(url, sizeof(url), "%s", argv[arg_i]);
            if (result_t < 0 || (size_t) result_t >= sizeof(url)) {
                printf("Parse error from package %s!\n", url);
                continue;
            }
            for (int i = 0; url[i] != '\0'; i++) {
                if (url[i] == '&' || url[i] == '\"' || url[i] == '|' || url[i] == ';' || url[i] == '/' || url[i] == '\\'
                    ||
                    url[i] == '.' || url[i] == '%' || url[i] == '<' || url[i] == '>' || url[i] == '(' || url[i] == ')'
                    ||
                    url[i] == '^' || url[i] == '!') {
                    printf("Unknown symbol '%c'!\n", url[i]);
                    return 1;
                }
            }
            char repo[1024] = "https://raw.githubusercontent.com/bytecompilier/BPM-registry/main/";
            char final[1024] = "";
            int result_s = snprintf(final, sizeof(final), "%s%s", repo, url);
            if (result_s < 0 || (size_t) result_s >= sizeof(final)) {
                printf("Parse error from package %s!\n", url);
                continue;
            }
            DeleteUrlCacheEntryA(final);
            HRESULT result = URLDownloadToFileA(NULL, final, "url", 0, NULL);
            if (result == E_ABORT) {
                printf("Download aborted in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == E_OUTOFMEMORY) {
                printf("Download out of memory in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == E_ACCESSDENIED) {
                printf("Download denied in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_NO_SESSION) {
                printf("Failed to open internet session in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_CANNOT_CONNECT) {
                printf("Failed to connect to internet server in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_RESOURCE_NOT_FOUND) {
                printf("Package not found in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_OBJECT_NOT_FOUND) {
                printf("Package not found in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_DATA_NOT_AVAILABLE) {
                printf("Package not available in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_DOWNLOAD_FAILURE) {
                printf("Download failed in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_CONNECTION_TIMEOUT) {
                printf("Connection timeout in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_CANNOT_INSTANTIATE_OBJECT) {
                printf("Cannot instantiate object in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_REDIRECT_FAILED) {
                printf("Redirect failed in package %s!\n", url);
                remove("url");
                continue;
            } else if (result == INET_E_SECURITY_PROBLEM) {
                printf("Security problem in package %s!\n", url);
                remove("url");
                continue;
            } else if (FAILED(result)) {
                printf("Code error: 0x%08lX in package %s\n", result, url);
                remove("url");
                continue;
            }
            dictionary *ini = iniparser_load("url");
            if (ini == NULL) {
                printf("Error opening file in package %s!\n", url);
                remove("url");
                continue;
            }
            const char *version = iniparser_getstring(ini, ":version", NULL);
            if (version == NULL) {
                printf("Error reading package %s!\n", url);
                iniparser_freedict(ini);
                remove("url");
                continue;
            }
            const char *author = iniparser_getstring(ini, ":author", NULL);
            if (author == NULL) {
                printf("Error reading package %s!\n", url);
                iniparser_freedict(ini);
                remove("url");
                continue;
            }
            printf("Downloading package %s (version %s by %s)!\n", url, version, author);
            char url2[1024] = "";
            const char *parsed_url = iniparser_getstring(ini, ":url", NULL);
            if (parsed_url == NULL) {
                printf("Error reading package %s!\n", url);
                iniparser_freedict(ini);
                remove("url");
                continue;
            }
            snprintf(url2, sizeof(url2), "%s", parsed_url);
            url2[strcspn(url2, "\r\n")] = 0;
            if (url2[0] == '\0') {
                printf("Empty URL in metafile in package %s!\n", url);
                remove("url");
                iniparser_freedict(ini);
                continue;
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
            dictionary *d = iniparser_load(".\\libs\\.parsed_version");
            if (d == NULL) {
                d = dictionary_new(0);
            }
            char key[1024] = "";
            snprintf(key, sizeof(key), ":%s", url);
            iniparser_set(d, "", NULL);
            iniparser_set(d, key, version);
            FILE *out_fp = fopen(".\\libs\\.parsed_version", "w");
            if (out_fp != NULL) {
                iniparser_dump_ini(d, out_fp);
                fclose(out_fp);
            }
            iniparser_freedict(d);
            iniparser_freedict(ini);
            HRESULT result_a = URLDownloadToFileA(NULL, url2, "main.zip", 0, NULL);
            if (result_a == E_ABORT) {
                printf("Download aborted in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == E_OUTOFMEMORY) {
                printf("Download out of memory in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == E_ACCESSDENIED) {
                printf("Download denied in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_NO_SESSION) {
                printf("Failed to open internet session in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_CANNOT_CONNECT) {
                printf("Failed to connect to internet server in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_RESOURCE_NOT_FOUND) {
                printf("Package %s not found!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_OBJECT_NOT_FOUND) {
                printf("Package %s not found!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_DATA_NOT_AVAILABLE) {
                printf("Package not available!\n");
                remove("url");
                continue;
            } else if (result_a == INET_E_DOWNLOAD_FAILURE) {
                printf("Download failed in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_CONNECTION_TIMEOUT) {
                printf("Connection timeout in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_CANNOT_INSTANTIATE_OBJECT) {
                printf("Cannot instantiate object in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_REDIRECT_FAILED) {
                printf("Redirect failed in package %s!\n", url);
                remove("url");
                continue;
            } else if (result_a == INET_E_SECURITY_PROBLEM) {
                printf("Security problem in package %s!\n", url);
                remove("url");
                continue;
            } else if (FAILED(result_a)) {
                printf("Code error: 0x%08lX in package %s\n", result_a, url);
                remove("url");
                continue;
            }
            printf("Unpacking package %s!\n", url);
            char array[1024] = "";
            char comm[1024] = "tar -xf main.zip --strip-components=1 -C \".\\libs\\";
            snprintf(array, sizeof(array), "%s%s\"", comm, url);
            int tar_res = system(array);
            if (tar_res != 0) {
                printf("Package %s unpacking failed!\n", url);
                remove("url");
                remove("main.zip");
                continue;
            }
            printf("Removing metafiles!\n");
            remove("main.zip");
            printf("Package %s successfully downloaded!\n", url);
        }
        return 0;
    } else if (argc >= 3 && strcmp(argv[1], "remove") == 0) {
        if (argc == 3 && strcmp(argv[2], "-y") == 0) {
            printf("Invalid args!\n");
            return 1;
        }
        bool test = true;
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-y") == 0) {
                test = false;
                break;
            }
        }
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-y") == 0) {
                continue;
            }
            char name[1024] = "";
            int result = snprintf(name, sizeof(name), "%s", argv[i]);
            if (result < 0 || (size_t) result >= sizeof(name)) {
                printf("Parse error!\n");
                return 1;
            }
            for (int i = 0; name[i] != '\0'; i++) {
                if (name[i] == '&' || name[i] == '\"' || name[i] == '|' || name[i] == ';' || name[i] == '/' || name[i]
                    ==
                    '\\' || name[i] == '.' || name[i] == '%' || name[i] == '<' || name[i] == '>' || name[i] == '(' ||
                    name[
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
                    continue;
                }
            }
            char remove_pkg[1024] = "";
            char dir[1024] = "rmdir /s /q \"libs\\";
            char nul[1024] = "2>nul";
            int result_t = snprintf(remove_pkg, sizeof(remove_pkg), "%s%s\" %s", dir, name, nul);
            if (result_t < 0 || (size_t) result_t >= sizeof(remove_pkg)) {
                printf("Parse error in package %s!\n", name);
                continue;
            }
            int result_s = system(remove_pkg);
            if (result_s == -1) {
                printf("Cmd cannot be executed!\n");
                return 1;
            } else if (result_s != 0) {
                printf("Package %s remove failed!\n", name);
                continue;
            }
            dictionary* ini = iniparser_load(".\\libs\\.parsed_version");
            if (ini == NULL) {
                printf("Package %s successfully removed!\n", name);
                return 0;
            }
            FILE * fp = fopen(".\\libs\\.parsed_version", "w");
            if (fp == NULL) {
                printf("File open error!\n");
                return 1;
            }
            char final_c[1024] = "";
            snprintf(final_c, sizeof(final_c), ":%s",name);
            iniparser_unset(ini, final_c);
            iniparser_dump_ini(ini, fp);
            fclose(fp);
            iniparser_freedict(ini);
            printf("Package %s successfully removed!\n", name);
        }
        return 0;
    }else if (argc >= 2 && strcmp(argv[1], "update") == 0) {
        dictionary* ini = iniparser_load(".\\libs\\.parsed_version");
        if (ini == NULL) {
            printf("Can't update no libraries found!\n");
            return 1;
        }
        int nkeys = iniparser_getsecnkeys(ini, "");
        if (nkeys <= 0) {
            printf("No installed libraries found!\n");
            iniparser_freedict(ini);
            return 0;
        }
        if (nkeys > 1024) {
            nkeys = 1024;
        }
        const char *packages[1024];
        iniparser_getseckeys(ini, "", packages);
        for (int i = 0; i < nkeys; i++) {
            const char *package = packages[i] +1;
            const char *local_ver = iniparser_getstring(ini, packages[i], NULL);
            char url[1024] = "";
            char url2[1024] = "https://raw.githubusercontent.com/bytecompilier/BPM-registry/main/";
            snprintf(url, sizeof(url), "%s%s",url2, package);
            DeleteUrlCacheEntryA(url);
            HRESULT result_a = URLDownloadToFileA(NULL, url, "url", 0, NULL);
            if (FAILED(result_a)) {
                printf("Code error: 0x%08lX\n", result_a);
                remove("url");
                continue;
            }
            dictionary* inih = iniparser_load("url");
            if (inih == NULL) {
                printf("Can't load url!\n");
                remove("url");
                continue;
            }
            const char *server_version = iniparser_getstring(inih, ":version", NULL);
            if (local_ver == NULL || server_version == NULL) {
                printf("Invalid version metadata for package %s!\n", package);
                iniparser_freedict(inih);
                remove("url");
                continue;
            }
            if (strcmp(local_ver, server_version) != 0) {
                const char *parsed_url = iniparser_getstring(inih, ":url", NULL);
                if (parsed_url == NULL) {
                    printf("Invalid URL metadata for package %s!\n", package);
                    iniparser_freedict(inih);
                    remove("url");
                    continue;
                }
                char rmdir[1024] = "";
                char com_rm[1024] = "rmdir /s /q \".\\libs\\";
                snprintf(rmdir, sizeof(rmdir), "%s%s\" 2>nul", com_rm, package);
                system(rmdir);
                char mkdir_cmd[1024] = "";
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir \".\\libs\\%s\" 2>nul", package);
                system(mkdir_cmd);
                DeleteUrlCacheEntryA(parsed_url);
                HRESULT dl_res = URLDownloadToFileA(NULL, parsed_url, "main.zip", 0, NULL);
                if (FAILED(dl_res)) {
                    printf("Failed to download update for %s (0x%08lX)\n", package, dl_res);
                    iniparser_freedict(inih);
                    remove("url");
                    continue;
                }
                char tar_cmd[1024] = "";
                snprintf(tar_cmd, sizeof(tar_cmd), "tar -xf main.zip --strip-components=1 -C \".\\libs\\%s\"", package);
                if (system(tar_cmd) != 0) {
                    printf("Failed to unpack update for %s!\n", package);
                    iniparser_freedict(inih);
                    remove("main.zip");
                    remove("url");
                    continue;
                }
                iniparser_set(ini, packages[i], server_version);
                printf("Package %s successfully updated to %s!\n", package, server_version);
                remove("main.zip");
            }
            else {
                printf("Package %s is already up to date (%s).\n", package, local_ver);
            }
            iniparser_freedict(inih);
            remove("url");
        }
        FILE *fp = fopen(".\\libs\\.parsed_version", "w");
        if (fp != NULL) {
            iniparser_dump_ini(ini, fp);
            fclose(fp);
        }
        iniparser_freedict(ini);
        return 0;
    }
    else if (strcmp(argv[1], "help") == 0 && argc == 2) {
        DWORD m = 0;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | 0x0004);
        printf("\033[1;36mBPM\033[0m - ByteC Package Manager\n\n");

        printf("\033[1;33mUsage:\033[0m\n");
        printf("  bpm \033[1;32m<command>\033[0m \033[90m[arguments]\033[0m\n\n");

        printf("\033[1;33mCommands:\033[0m\n");
        printf("  \033[1;32minstall\033[0m \033[90m<pkg1> [pkg2 ...]\033[0m     Install one or more packages from registry\n");
        printf("  \033[1;32mremove\033[0m  \033[90m<pkg1> [pkg2 ...]\033[0m     Remove installed packages (use -y to skip prompt)\n");
        printf("  \033[1;32mupdate\033[0m                        Update all installed packages to latest versions\n");
        printf("  \033[1;32mlist\033[0m                          Show all installed packages and versions\n");
        printf("  \033[1;32mhelp\033[0m                          Show this help message\n\n");

        printf("\033[1;33mExamples:\033[0m\n");
        printf("  \033[90mbpm install add std\033[0m\n");
        printf("  \033[90mbpm remove add -y\033[0m\n");
        printf("  \033[90mbpm update\033[0m\n");
        printf("  \033[90mbpm list\033[0m\n");
    }
    else if (strcmp(argv[1], "list") == 0 && argc == 2) {
        DWORD m = 0;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | 0x0004);
        dictionary* ini = iniparser_load(".\\libs\\.parsed_version");
        if (ini == NULL) {
            printf("No packages installed!\n");
            return 0;
        }
        int nkeys = iniparser_getsecnkeys(ini, "");
        if (nkeys <= 0) {
            printf("No packages installed.\n");
            iniparser_freedict(ini);
            return 0;
        }

        if (nkeys > 1024) {
            nkeys = 1024;
        }
        const char *packages[1024];
        iniparser_getseckeys(ini, "", packages);
        printf("\033[1;33mInstalled packages (%d):\033[0m\n", nkeys);
        for (int i = 0; i < nkeys; i++) {
            const char *pkg_name = packages[i] + 1;
            const char *ver = iniparser_getstring(ini, packages[i], "unknown");
            printf("  \033[1;32m%-16s\033[0m \033[90mv%s\033[0m\n", pkg_name, ver);
        }

        iniparser_freedict(ini);
        return 0;
    }
    else if (strcmp(argv[1], "init") == 0 && argc >= 2) {
        system("mkdir .\\libs 2>nul");
        system("type nul > .\\libs\\.parsed_version 2>nul");
        system("type nul > conf.ini 2>nul");
        printf("Successfully initialised project!\n");
        return 0;
    }
}
