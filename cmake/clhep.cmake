include(FetchContent)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND "CLHEP")


 FetchContent_Declare(
         ${PACKAGE_TO_FIND}
         GIT_REPOSITORY https://gitlab.cern.ch/CLHEP/CLHEP.git
         GIT_TAG CLHEP_2_4_5_1
         SOURCE_DIR ${CMAKE_BINARY_DIR}/clhep
         BINARY_DIR ${CMAKE_BINARY_DIR}/clhep-build
         # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
         CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/clhep -DCMAKE_CXX_FLAGS=-Wno-dev
 )












find_package(${PACKAGE_TO_FIND})

if(CLHEP_FOUND)
    message(STATUS "\n*** ${PACKAGE_TO_FIND} found ***")
    cmake_print_variables(CLHEP_VERSION)
    cmake_print_variables(CLHEP_DIR)
    cmake_print_variables(CLHEP_LIBRARIES)
    cmake_print_variables(CLHEP_INCLUDE_DIRS)
    message(STATUS "")
else()
    message(STATUS "\n* Fetching and configuring ${PACKAGE_TO_FIND} *")
    FetchContent_MakeAvailable(CLHEP)
    message(STATUS "")
endif()

message(STATUS "")


