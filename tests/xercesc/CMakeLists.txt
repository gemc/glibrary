# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(TEST_NAME "xercesc_glibrary_test")

project(${TEST_NAME} VERSION 1.0
        DESCRIPTION "Testing XercesC installation"
        LANGUAGES CXX)


### Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(XercesC)
endif()

# define test
add_test(
        NAME ${TEST_NAME}
        COMMAND $<TARGET_FILE:${TEST_NAME}>
)

# add executable
add_executable(${TEST_NAME} xercesc_test.cc)

# add include directories
target_include_directories(${TEST_NAME} PRIVATE ${XercesC_INCLUDE_DIRS})

# add linked libraries
target_link_libraries(${TEST_NAME} PRIVATE ${XercesC_LIBRARIES})

# set the C++ standard
target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)


# copy rga.xml to the build directory
configure_file(rga.xml rga.xml COPYONLY)


# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET xercesc_glibrary_test POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} --verbose
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running xercesc glibrary test"
            )
endif()

