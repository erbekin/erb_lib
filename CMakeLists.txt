cmake_minimum_required(VERSION 3.30)
project(ERB_LIB)

set(CMAKE_CXX_STANDARD 17)

add_library(ERB_LIB STATIC library.cpp)
target_include_directories(ERB_LIB PUBLIC include)