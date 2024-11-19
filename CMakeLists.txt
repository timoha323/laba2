cmake_minimum_required(VERSION 3.29)
project(laba2)

set(CMAKE_CXX_STANDARD 26)

add_executable(laba2 main.cpp
        interface.cpp
        test.cpp
        ${DATA_STRUCTURES}
        smart_pointers/functionalTests.cpp
        smart_pointers/Tests.cpp
        BubbleSorter.h)
