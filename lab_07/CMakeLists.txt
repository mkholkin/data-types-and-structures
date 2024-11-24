cmake_minimum_required(VERSION 3.28)
project(lab_07 C)

include_directories(include)

set(CMAKE_C_STANDARD 11)

add_executable(lab_07 main.c
        src/HashMap.c
        include/HashMap.h
        include/list.h
        src/list.c
        src/AVLTree.c
        include/AVLTree.h
        include/BSTree.h
        src/BSTree.c)
