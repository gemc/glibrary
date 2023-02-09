include(FetchContent)
include(glibrary_functions)
set(PACKAGE_TO_FIND CLHEP)

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://gitlab.cern.ch/CLHEP/CLHEP.git
        GIT_TAG CLHEP_2_4_5_1
        SOURCE_DIR  ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-source
        BINARY_DIR  ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-build
        INSTALL_DIR ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-install
        # The directories above should be added to the dependencies list in case of local install
        # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
        # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/clhep-build -DCMAKE_CXX_FLAGS=-Wno-dev
 )










# Adding local build directories to the search path
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-build ${CMAKE_PREFIX_PATH})
# find package must be in the main CMakeLists.txt
find_package(${PACKAGE_TO_FIND} QUIET)
# fetch if not found
glibrary_fetch_if_not_found(${PACKAGE_TO_FIND})






