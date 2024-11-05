cmake_minimum_required(VERSION 3.28)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "C:/SFML-2.6.1")
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(minesweeper main.cpp
        Cell.h
        Cell.cpp
        Grass.h
        Grass.cpp
        Mine.h
        Mine.cpp
        constants.h
        Field.h
        Field.cpp
        Renderer.h
        Renderer.cpp
        MyColors.h
        MyColors.cpp)

target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)