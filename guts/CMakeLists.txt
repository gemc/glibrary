# minimum version of CMake
cmake_minimum_required(VERSION 3.16...3.24)
set(LIBRARY_NAME guts)

project(${LIBRARY_NAME} VERSION 1.0
        DESCRIPTION "Various Glibrary Utilities"
        LANGUAGES CXX)


### Only do this for the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    include(clhep)
    include(glibrary)
endif()

#cmake_print_variables(CLHEP_FOUND)




add_library(${LIBRARY_NAME} SHARED)

# add include directories, public so who depends on this library will also link to them
target_include_directories(${LIBRARY_NAME} PUBLIC ${CLHEP_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/clhep-build)

# add link library, public so who depends on this library will also link to them
# target_link_libraries(${LIBRARY_NAME} PUBLIC ${CLHEP_LIBRARIES})

# set the C++ standard
target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)

# sources
target_sources(${LIBRARY_NAME} PRIVATE
        gutilities.cc gutsConventions.cc)


