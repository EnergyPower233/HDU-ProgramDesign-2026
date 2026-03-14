cmake_minimum_required(VERSION 4.0)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Snake
        gameGenerate.cpp
        gameStart.cpp
        Initialization.cpp
        main.cpp
        Snake.h
        UI.cpp)
