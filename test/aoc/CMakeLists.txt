add_executable(vec_test vec_test.c)
target_link_libraries(vec_test unity aoc)
add_test(vec_test vec_test)

add_executable(queue_test queue_test.c)
target_link_libraries(queue_test unity aoc)
add_test(queue_test queue_test)

add_executable(hashmap_test hashmap_test.c)
target_link_libraries(hashmap_test unity aoc)
add_test(hashmap_test hashmap_test)
