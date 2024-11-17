cmake_minimum_required(VERSION 3.28)
project(lab_06 C)

include_directories(include)

set(CMAKE_C_STANDARD 11)

add_executable(lab_06 main.c
        src/binary_tree.c
        include/binary_tree.h
        src/commands.c
        include/commands.h
        src/typed_files.c
        include/typed_files.h
        include/return_codes.h
        include/io.h
        src/io.c
        src/utils/string_tools.c
        src/utils/time.c
        include/utils/string_tools.h
        include/utils/time.h)
