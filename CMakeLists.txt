cmake_minimum_required(VERSION 4.3)
project(ByteC C)

set(CMAKE_C_STANDARD 11)

enable_language(RC)


add_executable(ByteC
        main.c
        preprocessor.c
)

add_executable(bytec_installer
        install.c
        resources.rc
)

add_executable(bytec_uninstaller
        deinstall.c
)

add_executable(bytec_editor
        editor.c
)


target_include_directories(bytec_editor PRIVATE "C:/vcpkg/installed/x64-mingw-dynamic/include")

target_link_libraries(bytec_editor PRIVATE
        "C:/vcpkg/installed/x64-mingw-dynamic/lib/libncurses.a"
        "C:/vcpkg/installed/x64-mingw-dynamic/lib/libpanel.a"
)