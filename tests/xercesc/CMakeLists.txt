# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(xercesc_test VERSION 1.0
        DESCRIPTION "Testing XercesC installation"
        LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(xercesc)
    enable_testing()
endif()

# add the xercesc_test main executable
add_executable(xercesc_test xercesc_test.cc)

# add xercesc include directories
target_include_directories(xercesc_test PRIVATE ${XercesC_INCLUDE_DIRS})


# link the xercesc_test executable with xercesc
target_link_libraries(xercesc_test PRIVATE ${XercesC_LIBRARIES})

# copy rga.xml to the build directory
configure_file(rga.xml rga.xml COPYONLY)


# define test
add_test(
        NAME xercesc_test
        COMMAND $<TARGET_FILE:xercesc_test>
)

# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET xercesc_test POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} --verbose
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running xercesc test"
            )
endif()

