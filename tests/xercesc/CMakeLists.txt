# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(xercesc_test VERSION 1.0
        DESCRIPTION "Testing XercesC installation"
        LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
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

# set the C++ standard
#target_compile_features(xercesc_test PRIVATE cxx_std_20)

# define test
add_test(
        NAME xercesc_test
        #COMMAND $<TARGET_FILE:xercesc_test>
        COMMAND xercesc_test
)


