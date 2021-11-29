
cmake_minimum_required(VERSION 3.18)
project(lapointe_algorithms
        VERSION 0.0.1
        DESCRIPTION "Set of algorithms"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

option(LaPointe_Enable_Test "Enable Unit Tests" ON)
option(LaPointe_Enable_Clang-Tidy "Enable Clang Tidy Checks" ON)

#add_library(lapointe_algorithms STATIC)

add_subdirectory(src)

if (LaPointe_Enable_Test)
    add_executable(test_lapointe_algorithms)

    #target_link_libraries(test_lapointe_algorithms PRIVATE lapointe_algorithms)
    add_subdirectory(test)
endif()

if (LaPointe_Enable_Clang)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()
