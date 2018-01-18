cmake_minimum_required(VERSION 3.9)
project(CRS_porr)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp" ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
SET(CMAKE_CXX_COMPILER mpicxx)

add_executable(CRS_porr main.cpp src/algorithm.cpp src/exercises.cpp)
target_link_libraries(CRS_porr ${MPI_LIBRARIES})
if(MPI_COMPILE_FLAGS)
    set_target_properties(CRS_porr PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(CRS_porr PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
target_link_libraries(CRS_porr ${MPI_LIBRARIES})
