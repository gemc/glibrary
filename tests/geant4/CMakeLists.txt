# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(TEST_NAME "geant4_glibrary_test")

project(${TEST_NAME} VERSION 1.0
        DESCRIPTION "Testing Geant4 installation"
        LANGUAGES CXX)


### Only do this for the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(geant4)
endif()

# define test
add_test(
        NAME ${TEST_NAME}
        COMMAND $<TARGET_FILE:${TEST_NAME}>
)

# add executable
add_executable(${TEST_NAME} geant4_test.cc)

# add include directories
target_include_directories(${TEST_NAME} PRIVATE ${Geant4_INCLUDE_DIR})

# add linked libraries
target_link_libraries(${TEST_NAME} PRIVATE ${Geant4_LIBRARIES})

# set the C++ standard
target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)






# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET geant4_test POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} --verbose
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running geant4 test"
            )
endif()

