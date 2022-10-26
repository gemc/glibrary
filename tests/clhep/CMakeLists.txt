# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(clhep_test VERSION 1.0
        DESCRIPTION "Testing CLHEP installation"
        LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    enable_testing()
endif()

# add the clhep_test main executable
add_executable(clhep_test clhep_test.cc)

# add clhep include directories
target_include_directories(clhep_test PRIVATE ${CLHEP_INCLUDE_DIRS})

# link the clhep_test executable with CLHEP
target_link_libraries(clhep_test PRIVATE CLHEP::CLHEP)

# set the C++ standard
target_compile_features(clhep_test PRIVATE cxx_std_20)

# define test
add_test(
        NAME clhep_test
        COMMAND $<TARGET_FILE:clhep_test>
)

# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET clhep_test POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running xercesc test"
        )
endif()