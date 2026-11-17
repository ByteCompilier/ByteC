cmake_minimum_required(VERSION 4.3)
project(ByteC C)

set(CMAKE_C_STANDARD 11)

enable_language(RC)


add_executable(ByteC
        main.c
        preprocessor.c
        dictionary.c
        iniparser.c
)

add_executable(bytec_installer
        install.c
        resources.rc
)


add_executable(bytec_uninstaller
        deinstall.c
)

add_executable(ByteEditor
        editor.c
)

target_link_libraries(ByteEditor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libterm.dll")
target_compile_definitions(ByteEditor PRIVATE LIBTERM_SHARED)

add_custom_command(TARGET ByteEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/libterm.dll"
        "$<TARGET_FILE_DIR:ByteEditor>"
)
add_executable(bpm Bpm.c)

target_link_libraries(bpm PRIVATE urlmon wininet pthread)