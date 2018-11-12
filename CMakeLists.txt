cmake_minimum_required(VERSION 3.12)
project(tv_shows_console_app)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        tv_shows_console_app
        main.cpp
        PieceOfCinematography.cpp
        PieceOfCinematography.h
        Series.cpp
        Series.h
        Movie.cpp
        Movie.h
        Livestream.cpp
        Livestream.h OperationsOnListOfPiecesOfCinematography.h Pool.cpp Pool.h CustomException.h FileNotFoundException.h)