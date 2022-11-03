include(FetchContent)
include(glibrary_functions)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND CLHEP)

 FetchContent_Declare(
         ${PACKAGE_TO_FIND}
         GIT_REPOSITORY https://gitlab.cern.ch/CLHEP/CLHEP.git
         GIT_TAG CLHEP_2_4_5_1
         SOURCE_DIR ${CMAKE_BINARY_DIR}/clhep-source
         BINARY_DIR ${CMAKE_BINARY_DIR}/clhep-build
         # The directories above should be added to the dependencies list in case of local install
         # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
         # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/clhep-build -DCMAKE_CXX_FLAGS=-Wno-dev
 )










GLIBRARY_FIND_PACKAGE(${PACKAGE_TO_FIND})






