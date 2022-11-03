include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PRINT_ALL_VARS "OFF" CACHE STRING "Print all cmake variables")

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(glibrary VERSION 1.0
        DESCRIPTION "A set of c++ libraries for general use"
        LANGUAGES CXX)

### add cmake to the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file).
    Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

### dependencies
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)

    include(clhep)
    #include(xercesc)
    #include(geant4)
    include(glibrary)
endif()

### tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME  AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

### glibraries
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(guts)
    add_subdirectory(goptions)
    add_subdirectory(gtouchable)
    add_subdirectory(gtranslationTable)
endif()


### Utilities: print all variables
if(PRINT_ALL_VARS)
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()