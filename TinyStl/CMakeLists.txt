cmake_minimum_required(VERSION 3.17)
project(TinyStl)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
include_directories(.)
set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(TinyStl main.cpp algobase.h)