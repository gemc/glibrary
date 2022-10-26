# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
project(geant4_test VERSION 1.0
        DESCRIPTION "Testing Geant4 installation"
        LANGUAGES CXX)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(USE_LOCAL_INSTALL "ON" CACHE STRING "Use Local Install")
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake" ${CMAKE_MODULE_PATH})
    include(geant4)
    enable_testing()
endif()

# add the geant4 main executable
add_executable(geant4_test geant4_test.cc)

# add xercesc include directories
target_include_directories(geant4_test PRIVATE ${Geant4_INCLUDE_DIR})


# link the xercesc_test executable with xercesc
target_link_libraries(geant4_test PRIVATE ${Geant4_LIBRARIES})


# define test
add_test(
        NAME geant4_test
        COMMAND $<TARGET_FILE:geant4_test>
)

# only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # run test after build
    add_custom_command(TARGET geant4_test POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} --verbose
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running geant4 test"
            )
endif()

