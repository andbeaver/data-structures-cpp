cmake_minimum_required(VERSION 3.17)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-static")
add_executable(Assignment_2
        src/main.cpp
        src/stack.h
        src/maze_solver.cpp
        src/maze_solver.h)
