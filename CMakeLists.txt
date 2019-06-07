cmake_minimum_required(VERSION 3.13)
project(ECSX)

option(BUILD_EXAMPLES "Build the example programs" off)

set(CMAKE_CXX_STANDARD 17)

if(BUILD_EXAMPLES)
	add_subdirectory("examples/")
endif()

file(GLOB_RECURSE sources "src/*.cpp")

add_library(ecsx ${sources})
target_compile_options(ecsx PUBLIC -Wall)
target_include_directories(ecsx PUBLIC "include/")