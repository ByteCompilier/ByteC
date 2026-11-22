cmake_minimum_required(VERSION 4.3)
project(ByteC C)

set(CMAKE_C_STANDARD 11)

enable_language(RC)


add_executable(ByteC
        src/dictionary/dictionary.c
        third_party/iniparser/iniparser.c
        src/vm/main.c
        src/parser/parser.c
        src/preprocessor/preprocessor.c
)

add_executable(bytec_installer
        src/installer/install.c
        resources.rc
)


add_executable(bytec_uninstaller
        src/installer/deinstall.c
)



add_executable(bpm src/bpm/Bpm.c src/dictionary/dictionary.c third_party/iniparser/iniparser.c
)

target_link_libraries(bpm PRIVATE urlmon wininet pthread)
add_dependencies(bytec_installer ByteC bpm)

set_source_files_properties(resources.rc PROPERTIES
        OBJECT_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ByteC.exe;${CMAKE_CURRENT_BINARY_DIR}/bpm.exe"
)
