project("Advent of Code" C)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

if(CODE_COVERAGE AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_subdirectory(external) 
add_subdirectory(src) 

enable_testing()
add_subdirectory(test)

