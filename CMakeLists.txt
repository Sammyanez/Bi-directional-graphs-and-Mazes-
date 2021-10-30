cmake_minimum_required(VERSION 3.20)
project(MZ1)

set(CMAKE_CXX_STANDARD 14)

add_executable(MZ1 main.cpp solve.h vertex.h solve.cpp vertex.cpp)
