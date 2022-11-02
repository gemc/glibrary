# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(LIBRARY_NAME "guts")

project(${LIBRARY_NAME} VERSION 1.0
        DESCRIPTION "Various Utilities"
        LANGUAGES CXX)


### Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    include(glibrary)
endif()

add_library(${LIBRARY_NAME} SHARED)

# add include directories
target_include_directories(${LIBRARY_NAME} PRIVATE ${CLHEP_INCLUDE_DIRS})

# sources
target_sources(${LIBRARY_NAME} PRIVATE
        gutilities.cc gutsConventions.cc)

# compiler flags
target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)


