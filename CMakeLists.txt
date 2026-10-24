cmake_minimum_required(VERSION 4.3)
project(ByteC C)

set(CMAKE_C_STANDARD 99)

enable_language(RC)

add_executable(ByteC main.c
)

add_executable(bytec_installer
        install.c
        resourses.rc
)

add_executable(bytec_uninstaller
        deinstall.c
)