# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(TEST_NAME clhep_glibrary_test)

project(${TEST_NAME} VERSION 1.0
        DESCRIPTION "Internal testing of CLHEP installation"
        LANGUAGES CXX)


### Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
endif()

# define test
add_test(
        NAME ${TEST_NAME}
        COMMAND $<TARGET_FILE:${TEST_NAME}>
)


add_executable(${TEST_NAME} clhep_test.cc)

# add include directories, nothing depends on this test so it's private
target_include_directories(${TEST_NAME} PUBLIC ${CLHEP_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/clhep-build)


# add linked libraries, nothing depends on this test so it's private
target_link_libraries(${TEST_NAME} PUBLIC ${CLHEP_LIBRARIES})

# set the C++ standard
target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)






# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET ${TEST_NAME} POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running ${TEST_NAME} test"
        )
endif()