cmake_minimum_required(VERSION 3.30)
project(ERB_LIB)

set(CMAKE_CXX_STANDARD 17)

add_library(erb-lib STATIC library.cpp)
target_include_directories(erb-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(erb::lib ALIAS erb-lib)