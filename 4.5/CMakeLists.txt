cmake_minimum_required(VERSION 3.17)
project(4_5)

set(CMAKE_CXX_STANDARD 17)
set(APP_SRC twoSum.cpp main.cpp isex.cpp)

add_executable(${PROJECT_NAME} ${APP_SRC})