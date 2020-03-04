cmake_minimum_required(VERSION 3.15)
project(af_FileSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(af_FileSystem main.cpp ui_filesystem.cpp ui_filesystem.h func_filesystem.cpp func_filesystem.h)