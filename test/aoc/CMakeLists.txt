add_executable(vec_test vec_test.c)
target_link_libraries(vec_test unity aoc)
add_test(vec_test vec_test)

add_executable(input_test input_test.c)
target_link_libraries(input_test unity aoc)
add_test(input_test input_test)
