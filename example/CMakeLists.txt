add_executable(memory-allocators-example main.cpp)

set_target_properties(
    memory-allocators-example PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "memory-allocators-example")
    target_compile_options(memory-allocators-example PRIVATE "/MP")
    set_target_properties(
        memory-allocators-example
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
endif()

# enable exceptions when using MSVC toolchain, makes Clang on windows possible
if(MSVC)
    target_compile_options(memory-allocators-example PRIVATE "-EHs")
endif()

target_link_libraries(
    memory-allocators-example

    PRIVATE
    memory-allocators
)
