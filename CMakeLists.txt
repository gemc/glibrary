include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(glibrary VERSION 1.0
        DESCRIPTION "A set of c++ libraries for general use"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

cmake_print_variables(CMAKE_CXX_STANDARD)

# add cmake to the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(clhep)
#include(xercesc)

# add glibraries
add_subdirectory(gtranslationTable)