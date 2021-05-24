set(PROJECT_BENCHMARKING_SOURCE_FILES
    benchmark_main.cpp

    pool_allocator/pool_allocator.cpp
)

add_executable(memory-allocators-benchmarks ${PROJECT_BENCHMARKING_SOURCE_FILES})

set_target_properties(
    memory-allocators-benchmarks PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    memory-allocators-benchmarks

    PRIVATE
    memory-allocators
)
