# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(gtests VERSION 1.0
        DESCRIPTION "A set of tests for glibrary"
        LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")

    # only if this is the main project
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    include(xercesc)
    enable_testing()
endif()

add_subdirectory(clhep)
add_subdirectory(xercesc)
