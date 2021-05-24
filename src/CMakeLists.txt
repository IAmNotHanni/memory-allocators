set(PROJECT_SOURCE_FILES
    allocators/pool_allocator/pool_allocator.cpp
)

foreach(FILE ${PROJECT_SOURCE_FILES})
    get_filename_component(PARENT_DIR "${FILE}" PATH)

    string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")

    if("${FILE}" MATCHES ".*\\.cpp")
        set(GROUP "Source Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
        set(GROUP "Header Files\\${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(memory-allocators ${PROJECT_SOURCE_FILES})

set_target_properties(
    memory-allocators PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# enable multi processor building if VS project
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    target_compile_options(memory-allocators PRIVATE "/MP")
endif()

# enable exceptions when using MSVC toolchain, makes Clang on windows possible
if(MSVC)
    target_compile_options(memory-allocators PRIVATE "-EHs")
endif()

target_include_directories(
    memory-allocators

    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

if(CONAN_LIBS)
    target_link_libraries(
        memory-allocators

        PUBLIC
        ${CONAN_LIBS}
    )
else()
    foreach(_LIB ${CONAN_LIBS_RELEASE})
        target_link_libraries(
            memory-allocators
            optimized

            ${_LIB}
        )
    endforeach()
    foreach(_LIB ${CONAN_LIBS_DEBUG})
        target_link_libraries(
            memory-allocators
            debug

            ${_LIB}
        )
    endforeach()
endif()
