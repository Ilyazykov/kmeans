cmake_minimum_required(VERSION 3.15)
project(kmeans)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    if(APPLE)
        include_directories(/System/Volumes/Data/usr/local/Cellar/libomp/9.0.0/include)
        link_directories(/System/Volumes/Data/usr/local/Cellar/libomp/9.0.0/lib)
    endif()
endif()



add_executable(kmeans main.cpp Point.h Point.cpp Point.h functions.h functions.cpp kmeans.h kmeans.cpp)

if (OPENMP_FOUND)
elseif(APPLE)
    target_link_libraries(kmeans libomp.a)
endif()
