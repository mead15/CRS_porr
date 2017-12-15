cmake_minimum_required(VERSION 3.9)
project(CRS_porr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(CRS_porr main.cpp src/algorithm.cpp src/exercises.cpp)