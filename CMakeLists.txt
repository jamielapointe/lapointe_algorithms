
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

# Get third party requires
include(FetchContent)

# Get GoogleTest version 1.11.0
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
)

# Get GoogleBenchmark version 1.6.1
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG master
  )

  FetchContent_MakeAvailable(googletest googlebenchmark)
.0
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "Disable Google benchmark tests")

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(src)

if (LaPointe_Enable_Test)
    add_executable(test_lapointe_algorithms)
    target_include_directories(test_lapointe_algorithms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures
                                                                ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures/sort
                                                                ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(test_lapointe_algorithms PRIVATE gtest_main)
    add_subdirectory(test)
endif()

# if (LaPointe_Enable_Benchmarks)
#   add_executable(benchmark_lapointe_algorithms)
#   target_include_directories(benchmark_lapointe_algorithms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
#                                                                    ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures
#                                                                    ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures/sort
#                                                                    ${CMAKE_CURRENT_SOURCE_DIR})
#   target_link_libraries(benchmark_lapointe_algorithms PRIVATE gtest_main)
#   add_subdirectory(benchmark)
# endif()

if (LaPointe_Enable_Clang-Tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;)
endif()
