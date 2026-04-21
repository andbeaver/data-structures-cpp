cmake_minimum_required(VERSION 3.25)
project(Assignment1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-static")
add_executable(edit
        src/main.cpp
        src/editor.cpp
        src/editor.h
        src/linked_list.cpp
        src/linked_list.h
)
