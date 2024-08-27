cmake_minimum_required(VERSION 3.5)

project(07.homework)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    #By default, new Visual Studio projects link the C runtimes dynamically
    #but GoogleTest links them statically. This will generate an error
    #Enabling this option will make gtest link the runtimes dynamically too
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

# Build googletest
add_subdirectory(googletest)

# Main target
add_subdirectory(otus-cpp-basic-hw06)

# Test target
add_executable(
        containers_tests
        test/containers_tests.cpp
        test/dynamic_container_tests.cpp
        test/bidirectional_list_container_tests.cpp
)

# Add src to the include directories for the test target
target_include_directories(
        containers_tests PRIVATE
        otus-cpp-basic-hw06
)

# Link test target against gtest libraries
target_link_libraries(
        containers_tests PRIVATE
        gtest gtest_main
)

set_target_properties(containers_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(
            containers_tests PRIVATE
            /W4
    )
else ()
    target_compile_options(
            containers_tests PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif ()
