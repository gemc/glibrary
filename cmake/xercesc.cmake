include(FetchContent)
set(PACKAGE_TO_FIND XercesC)

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://github.com/apache/xerces-c
        GIT_TAG v3.2.3
        SOURCE_DIR ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-source
        BINARY_DIR ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-build
        # The directories above should be added to the dependencies list in case of local install
        # the  -Wno-dev  flag is to ignore the project developers cmake warnings for policy CMP0077
        # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/xercesc -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-Wno-dev
)











# Adding XERCESCROOT and local build directories to the search path.
#set(CMAKE_PREFIX_PATH $ENV{XERCESCROOT} ${CMAKE_BINARY_DIR}/${PACKAGE_TO_FIND}-build  ${CMAKE_PREFIX_PATH})

# find package must be in the main CMakeLists.txt
find_package(${PACKAGE_TO_FIND} QUIET)

# fetch if not found
#glibrary_fetch_if_not_found(${PACKAGE_TO_FIND})
