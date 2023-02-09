# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(LIBRARY_NAME "gtranslationTable")

project(${LIBRARY_NAME} VERSION 1.0
        DESCRIPTION "Provides mapping between a detector identifier and a translation table"
        LANGUAGES CXX)


### Only do this for the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(glibrary)
endif()


add_library(${LIBRARY_NAME} SHARED)

# add include directories
target_include_directories(${LIBRARY_NAME} PRIVATE ${CLHEP_INCLUDE_DIRS})
target_include_directories(${LIBRARY_NAME} PRIVATE ${GLIBRARIES_INC_DIRS})


# sources
target_sources(${LIBRARY_NAME} PRIVATE
        gtranslationTable.cc gtranslationTableOptions.cc)

target_link_libraries(${LIBRARY_NAME} PRIVATE guts gtouchable)

# compiler flags
target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)






