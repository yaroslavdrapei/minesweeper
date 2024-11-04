cmake_minimum_required(VERSION 3.28)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper main.cpp
        Cell.h
        Cell.cpp
        Grass.h
        Grass.cpp
        Mine.h
        Mine.cpp
        constants.h
        Field.h
        Field.cpp)
