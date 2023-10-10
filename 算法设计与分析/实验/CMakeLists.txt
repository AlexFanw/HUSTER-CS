cmake_minimum_required(VERSION 3.0.0)
project(poj VERSION 0.1.0)


enable_testing()

add_executable(poj main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
