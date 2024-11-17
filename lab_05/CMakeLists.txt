cmake_minimum_required(VERSION 3.28)
project(lab_05 C)

include_directories(include)

set(CMAKE_C_STANDARD 11)

add_executable(lab_05 main.c
        include/return_codes.h
        src/sa_queue.c
        include/sa_queue.h
        src/list.c
        include/list.h
        src/ll_queue.c
        include/ll_queue.h
        include/types.h
        include/simuation.h
        src/simulation.c
        include/utils.h
        src/commands.c
        include/commands.h
        src/io.c
        include/utils/string_tools.h
        include/utils/time.h
        include/io.h
        src/utils/string_tools.c
        src/utils/time.c
        src/validators.c
        include/validators.h
        src/iinput_funcs.c
        include/iinput_funcs.h)


add_executable(measure measure.c
        include/return_codes.h
        src/sa_queue.c
        include/sa_queue.h
        src/list.c
        include/list.h
        src/ll_queue.c
        include/ll_queue.h
        include/types.h
        include/simuation.h
        src/simulation.c
        include/utils.h
        src/commands.c
        include/commands.h
        src/io.c
        include/utils/string_tools.h
        include/utils/time.h
        include/io.h
        src/utils/string_tools.c
        src/utils/time.c
        src/validators.c
        include/validators.h
        src/iinput_funcs.c
        include/iinput_funcs.h)
