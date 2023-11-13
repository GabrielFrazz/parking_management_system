cmake_minimum_required(VERSION 3.26)
project(PARKING_MANAGEMENT_SYSTEM)

set(CMAKE_CXX_STANDARD 17)

add_executable(PARKING_MANAGEMENT_SYSTEM main.cpp
        customer.cpp
        customer.h
        parking_lot.cpp
        parking_lot.h
        searches.cpp
        searches.h
        UI.cpp
        UI.h
)
