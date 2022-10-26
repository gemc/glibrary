include(CMakePrintHelpers) # to print variables with cmake_print_variables

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(gtests VERSION 1.0
        DESCRIPTION "A set of tests for glibrary"
        LANGUAGES CXX)

#include(CTest)

add_subdirectory(tests)
