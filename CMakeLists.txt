project("Advent of Code" C)

cmake_minimum_required(VERSION 3.18)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

if ( CMAKE_COMPILER_IS_GNUCC )
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
endif()
if ( MSVC )
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /W4")
endif()

if(CODE_COVERAGE AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_subdirectory(external) 
add_subdirectory(src) 

enable_testing()
add_subdirectory(test)

