cmake_minimum_required(VERSION 3.28)
project(lab_04 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lab_04 main.c
        include/return_codes.h
        include/ll_stack.h
        src/ll_stack.c
        include/da_stack.h
        src/da_stack.c
        include/types.h
        src/commands.c
        include/commands.h
        src/io/io.c
        include/io/io.h
        src/utils/string_tools.c
        include/utils/string_tools.h
        src/sa_stack.c
        include/sa_stack.h
        src/io/ptr_io.c
        include/io/ptr_io.h
        src/io/validators.c
        include/io/validators.h
        src/utils/time.c
        include/utils/time.h
        src/utils/utils.c
        include/utils/utils.h)


add_executable(measure measure.c
        include/return_codes.h
        include/ll_stack.h
        src/ll_stack.c
        include/da_stack.h
        src/da_stack.c
        include/types.h
        src/commands.c
        include/commands.h
        src/io/io.c
        include/io/io.h
        src/utils/string_tools.c
        include/utils/string_tools.h
        src/sa_stack.c
        include/sa_stack.h
        src/io/ptr_io.c
        include/io/ptr_io.h
        src/io/validators.c
        include/io/validators.h
        src/utils/time.c
        include/utils/time.h
        src/utils/utils.c
        include/utils/utils.h)
