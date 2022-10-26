include(CMakePrintHelpers) # to print variables with cmake_print_variables

# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(clhep_test VERSION 1.0
        DESCRIPTION "Testing CLHEP installation"
        LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # only if this is the main project
    # add the CLHEP package
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})

    include(clhep)


endif()

# add the clhep_test main executable
add_executable(clhep_test clhep_test.cc)

# link the clhep_test executable with CLHEP
target_link_libraries(clhep_test PRIVATE CLHEP::CLHEP)

# set the C++ standard
target_compile_features(clhep_test PRIVATE cxx_std_17)




