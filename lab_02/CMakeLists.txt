cmake_minimum_required(VERSION 3.28)
project(lab_02 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab_02 main.c
        include/types.h
        src/utils/string_tools.c
        include/utils/string_tools.h
        src/io/io.c
        include/io/io.h
        include/return_codes.h
        src/io/validators.c
        include/io/validators.h
        src/io/cars_io.c
        include/io/cars_io.h
        include/defines.h
        src/algorithm/sorting.c
        include/algorithm/sorting.h
        src/algorithm/key_table.c
        include/algorithm/key_table.h
        src/process.c
        include/process.h
        src/utils/time.c
        include/utils/time.h)
