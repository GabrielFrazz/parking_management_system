cmake_minimum_required(VERSION 3.26)

project(parking_management_system)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES "*.cpp")

add_executable(parking_management_system ${SOURCES})

