set(PROJECT_UNIT_TEST_SOURCE_FILES
    unit_tests_main.cpp

    pool_allocator/pool_allocator.cpp
)

add_executable(memory-allocators-tests ${PROJECT_UNIT_TEST_SOURCE_FILES})

set_target_properties(
    memory-allocators-tests PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    memory-allocators-tests

    PRIVATE
    memory-allocators
)
