cmake_minimum_required(VERSION 3.20)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(checkers
        coord.h
        main.cpp
        game.cpp
        game.h
        motions.cpp
        motions.h)
