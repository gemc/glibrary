include(FetchContent)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND "XercesC")

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://github.com/apache/xerces-c
        GIT_TAG v3.2.3
        SOURCE_DIR ${CMAKE_BINARY_DIR}/xercesc
        BINARY_DIR ${CMAKE_BINARY_DIR}/xercesc-build

        # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/xercesc -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-Wno-dev
)

# CMAKE_PREFIX_PATH is used by find_package to find the xercesc-config.cmake file
set(CMAKE_PREFIX_PATH "$ENV{XERCESCROOT}" ${CMAKE_INCLUDE_PATH})








find_package(${PACKAGE_TO_FIND})

if(XercesC_FOUND)
    message(STATUS "\n*** ${PACKAGE_TO_FIND} found ***")
    cmake_print_variables(XercesC_VERSION)
    cmake_print_variables(XercesC_INCLUDE_DIRS)
    cmake_print_variables(XercesC_LIBRARY)
    message(STATUS "")
else()
    message(STATUS "\n* Fetching and configuring ${PACKAGE_TO_FIND} *")
    FetchContent_MakeAvailable(xercesc)
    message(STATUS "")
endif()

message(STATUS "")
FetchContent_GetProperties(XercesC)

