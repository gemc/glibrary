include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PRINT_ALL_VARS "OFF" CACHE STRING "Print all cmake variables")

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(glibrary VERSION 1.0
        DESCRIPTION "A set of c++ libraries for general use"
        LANGUAGES CXX)

### add cmake to the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL TRUE)


### dependencies
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)

    include(glibrary_functions)
    require_out_of_source_build()

    include(clhep)
    include(xercesc)
    #include(geant4)
    include(glibrary)
endif()




### tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

### glibraries
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(guts)
    add_subdirectory(goptions)
    add_subdirectory(gtouchable)
    add_subdirectory(gtranslationTable)
endif()


if(PRINT_ALL_VARS)
    print_all_variables()
endif()
