cmake_minimum_required(VERSION 4.1)
project(Tarea_X)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Tarea_X
        AVL.cpp
        AVL.h
        main.cpp
        Student.h)
