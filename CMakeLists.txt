cmake_minimum_required(VERSION 3.29)
project(laba2)

set(CMAKE_CXX_STANDARD 26)

add_executable(laba2 main.cpp
        interface.cpp
        test.cpp
        ${DATA_STRUCTURES}
        smart_pointers/Tests.cpp
        BubbleSorter.h
        DataStructures/ArraySequence.tpp
        DataStructures/DynamicArray.tpp
        DataStructures/ImmutableArraySequence.tpp
        DataStructures/LinkedList.tpp
        DataStructures/ListSequence.tpp
        DataStructures/LinkedListSmart.h
        DataStructures/ListSequence.h
        DataStructures/DynamicArraySmart.h
        DataStructures/ArraySequence.h
        DataStructures/ImmutableSequence.h
        CountingSorter.h
        fileSorting.h
        fileSorting.cpp)
