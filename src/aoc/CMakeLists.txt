add_library(aoc STATIC
	common.c
	common.h
	vec.c
	vec.h
)

target_include_directories(aoc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
