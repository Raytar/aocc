add_library(2021 STATIC
	2021.h
	2021.c
	solutions.h
	datastructures.c
	datastructures.h
	day1.c
	day2.c
	day3.c
	day4.c
	day5.c
	day6.c
	day7.c
)

target_link_libraries(2021 aoc)

target_include_directories(2021 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
