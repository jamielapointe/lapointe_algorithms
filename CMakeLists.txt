
cmake_minimum_required(VERSION 3.18)
project(lapointe_algorithms
    VERSION 0.0.1
    DESCRIPTION "Practics set of basic algorithms"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

option(LaPointe_Enable_Test "Enable Unit Tests" ON)
option(LaPointe_Enable_Benchmarks "Enable Benchmarks" ON)
option(LaPointe_Enable_Clang-Tidy "Enable Clang Tidy Checks" ON)

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)
option(BENCHMARK_ENABLE_GTEST_TESTS "Disable Benchmark Dependency on Google Test" OFF)

# option(BENCHMARK_ENABLE_EXCEPTIONS "Enable the use of exceptions in the benchmark library." OFF)
# option(BENCHMARK_ENABLE_LTO "Enable link time optimisation of the benchmark library." ON)
# option(BENCHMARK_ENABLE_LIBPFM "Enable performance counters provided by libpfm" OFF)

# Place third party above clang-tidy and above any other compiler manipulation
add_subdirectory(third_party)

if(LaPointe_Enable_Clang-Tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()

add_executable(benchmark_lapointe_algorithms)
target_link_libraries(benchmark_lapointe_algorithms benchmark)

find_library(TBB_LIBRARY tbb)

if(DEFINED TBB_LIBRARY)
    set(TBB_LIBRARY_FOUND ON)
    target_link_libraries(benchmark_lapointe_algorithms tbb)
endif()

add_executable(test_lapointe_algorithms)
target_link_libraries(test_lapointe_algorithms gtest_main)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/compare
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/graphs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/sort
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures
    ${CMAKE_CURRENT_SOURCE_DIR}/src/leet
    ${CMAKE_CURRENT_SOURCE_DIR}/src/multiplication
    ${CMAKE_BINARY_DIR})

if(MSVC)
else()
    target_compile_options(test_lapointe_algorithms PRIVATE -Weverything
        -Werror
        -Wno-pre-c++17-compat
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-global-constructors
        -Wno-padded)
endif()

add_subdirectory(src)
add_subdirectory(benchmark)
add_subdirectory(test)

configure_file(cmake/lapointe_algorithms_config.h.in lapointe_algorithms_config.h)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS benchmark_lapointe_algorithms test_lapointe_algorithms
    PUBLIC_HEADER
    PRIVATE_HEADER)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/data/ DESTINATION data/)
