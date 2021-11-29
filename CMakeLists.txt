project("Advent of Code" C)

cmake_minimum_required(VERSION 3.0)

add_subdirectory(external) 
add_subdirectory(src) 

enable_testing()
add_subdirectory(test)

