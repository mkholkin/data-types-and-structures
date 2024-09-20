cmake_minimum_required(VERSION 3.28)
project(lab_01 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_01 main.c
        include/array_tools.h
        include/defines.h
        include/extended_arithmetic.h
        include/types.h
        include/ui.h
        src/array_tools.c
        src/extended_arithmetic.c
        src/ui.c
        include/return_codes.h)
