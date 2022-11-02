# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(gtests VERSION 1.0
        DESCRIPTION "A set of tests for glibrary"
        LANGUAGES CXX)

### Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)

    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    include(xercesc)
endif()

# only run if the proper library is found
if(CLHEP_FOUND)
    add_subdirectory(clhep)
endif()

if(XercesC_FOUND)
    add_subdirectory(xercesc)
endif()

if(Geant4_FOUND)
    add_subdirectory(geant4)
endif()
