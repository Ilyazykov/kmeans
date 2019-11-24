cmake_minimum_required(VERSION 3.15)
project(kmeans)

set(CMAKE_CXX_STANDARD 11)

add_executable(kmeans main.cpp Point.h Point.cpp Point.h functions.h functions.cpp kmeans.h kmeans.cpp)