cmake_minimum_required(VERSION 3.20)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

include_directories(Board)
include_directories(Figures)
include_directories(Pieces)
include_directories(Util)

add_executable(checkers
        Board/Board.cpp
        Board/Board.h
        Figures/Normal.cpp
        Figures/Normal.h
        Figures/Queen.cpp
        Figures/Queen.h
        Pieces/Piece.cpp
        Pieces/Piece.h
        Pieces/Square.cpp
        Pieces/Square.h
        Util/MoveUtil.cpp
        Util/MoveUtil.h
        main.cpp)
