cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(spellcheck
        src/main.cpp
        src/bst.h
        src/spell_checker.h)
