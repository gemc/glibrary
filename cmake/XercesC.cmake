include(FetchContent)
include(glibrary_functions)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND XercesC)

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://github.com/apache/xerces-c
        GIT_TAG v3.2.3
        SOURCE_DIR ${CMAKE_BINARY_DIR}/xercesc-source
        BINARY_DIR ${CMAKE_BINARY_DIR}/xercesc-build
        # The directories above should be added to the dependencies list in case of local install
        # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
        # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/xercesc -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-Wno-dev
)

# CMAKE_PREFIX_PATH set here so libraries depending on this package can find it
set(CMAKE_PREFIX_PATH $ENV{XERCESCROOT} ${CMAKE_BINARY_DIR}/xercesc-build ${CMAKE_PREFIX_PATH})








GLIBRARY_FIND_PACKAGE(${PACKAGE_TO_FIND})

