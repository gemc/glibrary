# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(glibrary_tests VERSION 1.0
        DESCRIPTION "A set of tests for glibrary"
        LANGUAGES CXX)

### Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    include(xercesc)
endif()

# only run if the proper library is found
# TODO: can we add clhep dependency here so this will compile after clhep is built?

#include(CMakePrintHelpers) # to print variables with cmake_print_variables
#cmake_print_variables(CLHEP_FOUND)


#if(CLHEP_FOUND)
    add_subdirectory(clhep)
#endif()

if(XercesC_FOUND)
    add_subdirectory(xercesc)
endif()

if(Geant4_FOUND)
    add_subdirectory(geant4)
endif()
