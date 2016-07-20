cmake_minimum_required (VERSION 2.6)
project ("CDR Generic Decoder")
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -ggdb3")
add_library(cdrasn1 SHARED
		parser.cpp)
