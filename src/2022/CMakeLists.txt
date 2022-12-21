add_library(2022 STATIC
	2022.h
	2022.c
	solutions.h
	day1.c
)

target_link_libraries(2022 aoc)

target_include_directories(2022 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
