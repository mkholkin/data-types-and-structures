cmake_minimum_required(VERSION 3.29)
project(lab_03 C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_executable(lab_03 main.c
        include/types.h
        include/return_codes.h
        include/return_codes.h
        include/types.h
        src/matrix_operations.c
        include/matrix_operations.h
        src/commands.c
        include/commands.h
        src/io/io.c
        include/io/io.h
        src/utils/string_tools.c
        include/utils/string_tools.h
        src/io/matrix_io.c
        include/io/matrix_io.h
        src/io/validators.c
        include/io/validators.h
        src/utils/utils.c
        include/utils/utils.h
        include/utils/time.h
        src/utils/time.c
        measure.c)