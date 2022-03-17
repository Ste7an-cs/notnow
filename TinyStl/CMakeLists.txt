cmake_minimum_required(VERSION 3.17)
project(TinyStl)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(TinyStl main.cpp)