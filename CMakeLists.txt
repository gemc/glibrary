include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")
set(PRINT_ALL_VARS "OFF" CACHE STRING "Print all cmake variables")

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(glibrary VERSION 1.0
        DESCRIPTION "A set of c++ libraries for general use"
        LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 20)
#cmake_print_variables(CMAKE_CXX_STANDARD)

# add cmake to the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(clhep)
    include(xercesc)
    include(geant4)

    # Run tests before compiling the libraries
    # Notice these will not be added if the dependencies are not found
    # Re-running cmake will add them
    enable_testing()
    add_subdirectory(tests)

    # add glibraries
    #add_subdirectory(gtranslationTable)
endif()


if(PRINT_ALL_VARS)
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()