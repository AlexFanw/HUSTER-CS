cmake_minimum_required(VERSION 3.13)
project(TCP)


set(CMAKE_EXE_LINKER_FLAGS "-static")
SET(CMAKE_C_COMPTLER GCC)
add_definitions(-std=c++11)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
ADD_EXECUTABLE(TCP ${SRC_LIST} src/TCP.cpp src/TCPSender.cpp include/TCPSender.h include/TCPReceiver.h src/TCPReceiver.cpp)
FIND_LIBRARY(NETSIM_LIB libnetsim.a ${PROJECT_SOURCE_DIR}/lib)
TARGET_LINK_LIBRARIES(TCP  ${NETSIM_LIB})