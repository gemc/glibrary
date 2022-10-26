# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(gtranslationTable VERSION 1.0
        DESCRIPTION "Provides mapping between a detector identifier and a translation table"
        LANGUAGES CXX)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")

    # only if this is the main project
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

endif()

set(SOURCES gtranslationTable.cc)

# add library from SOURCES
add_library(gtranslationTable SHARED ${SOURCES})

# add include directories
#target_include_directories(gtranslationTable PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#        $<INSTALL_INTERFACE:.>
#        )

