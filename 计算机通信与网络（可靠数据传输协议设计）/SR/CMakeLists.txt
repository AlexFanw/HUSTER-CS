cmake_minimum_required(VERSION 3.13)
project(StopWait)


SET(CMAKE_C_COMPTLER GCC)
add_definitions(-std=c++11)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
ADD_EXECUTABLE(SR ${SRC_LIST} src/SR.cpp src/SRSender.cpp src/SRReceiver.cpp include/SRSender.h include/SRReceiver.h)
FIND_LIBRARY(NETSIM_LIB libnetsim.a ${PROJECT_SOURCE_DIR}/lib)
TARGET_LINK_LIBRARIES(SR  ${NETSIM_LIB})