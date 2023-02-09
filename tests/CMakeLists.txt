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
    include(geant4)
endif()

# only run each test if the proper library is found
if(CLHEP_FOUND)
    add_subdirectory(clhep)
else()
    message(STATUS "CLHEP not found, skipping CLHEP internal tests. Try again when CLHEP is installed.")
endif()

if(XercesC_FOUND)
    add_subdirectory(xercesc)
else()
    message(STATUS "XercesC not found, skipping XercesC internal tests. Try again when XercesC is installed.")
endif()

if(Geant4_FOUND)
    add_subdirectory(geant4)
else()
    message(STATUS "Geant4 not found, skipping Geant4 internal tests. Try again when Geant4 is installed.")
endif()
