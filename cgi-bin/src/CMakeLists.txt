cmake_minimum_required(VERSION 3.24)
project(CheckTheNum)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(CheckTheNum main.cpp utils.h index.h)
