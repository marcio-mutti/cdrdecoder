cmake_minimum_required (VERSION 2.6)
project ("cdrasn1")
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb3")
add_library(cdrasn1 SHARED
		parser.cpp
		definitions.cpp
		auxfun.cpp
#		tags.cpp
		defloader.cpp)
target_compile_features(cdrasn1 PUBLIC
	cxx_nullptr
	cxx_lambdas)

