cmake_minimum_required(VERSION 3.19)
project(MultiMapSLL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MultiMapSLL
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h)
