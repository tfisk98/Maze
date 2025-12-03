cmake_minimum_required(VERSION 4.1.2)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_library(maze src/main.cpp)
