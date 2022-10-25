# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(gtranslationTable VERSION 1.0
        DESCRIPTION "Provides mapping between a detector identifier and a translation table"
        LANGUAGES CXX)



# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    include(CMakePrintHelpers) # to print variables

    cmake_print_variables(CMAKE_CXX_STANDARD)

    # add ../cmake to the module path
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

    include(clhep)

endif()
