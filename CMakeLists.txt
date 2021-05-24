cmake_minimum_required(VERSION 3.9)

# https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
cmake_policy(SET CMP0091 NEW)

project(memory-allocators)

# Stop in source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Options
option(ALLOCATORS_BUILD_BENCHMARKS "Build benchmarks" ON)
option(ALLOCATORS_BUILD_EXAMPLE "Build example" ON)
option(ALLOCATORS_BUILD_TESTS "Build tests" ON)

message(STATUS "ALLOCATORS_BUILD_BENCHMARKS = ${ALLOCATORS_BUILD_BENCHMARKS}")
message(STATUS "ALLOCATORS_BUILD_EXAMPLE = ${ALLOCATORS_BUILD_EXAMPLE}")
message(STATUS "ALLOCATORS_BUILD_TESTS= ${ALLOCATORS_BUILD_TESTS}")

message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Dependency setup with conan
include(conan_setup)

add_subdirectory(src)

if(ALLOCATORS_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(ALLOCATORS_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(ALLOCATORS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
