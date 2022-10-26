include(FetchContent)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
# https://cmake.org/cmake/help/latest/module/FindXercesC.html

FetchContent_Declare(
        xercesc
        GIT_REPOSITORY https://github.com/apache/xerces-c
        GIT_TAG v3.2.3
)


# try local installation if USE_LOCAL_INSTALL is set
if(USE_LOCAL_INSTALL STREQUAL "ON")
    # set variables from environment
    set(XERCESCROOT     $ENV{XERCESCROOT}     CACHE PATH "Path to XercesC")
    get_filename_component(XercesC_VERSION ${XERCESCROOT} NAME)

    # sets XercesC_LIBRARY and XercesC_INCLUDE_DIR
    find_library(
            XercesC_LIBRARY
            NAMES xerces-c
            PATHS ${XERCESCROOT}
            PATH_SUFFIXES lib64 lib32 lib
            NO_DEFAULT_PATH
    )

    find_path(
            XercesC_INCLUDE_DIR
            NAMES xercesc/dom/DOM.hpp
            PATHS ${XERCESCROOT}
            PATH_SUFFIXES include
            NO_DEFAULT_PATH
    )

endif()

# find XercesC
find_package(XercesC)

if(XercesC_FOUND)
    message(STATUS "")
    message(STATUS "* A local install of XercesC was found - using it*")
    message(STATUS "")
else()
    message(STATUS "")
    message(STATUS "* XercesC was not found - Fetching and installing it *")
    FetchContent_MakeAvailable(xercesc)
    message(STATUS "")
endif()

cmake_print_variables(XercesC_INCLUDE_DIRS)
cmake_print_variables(XercesC_LIBRARY)
message(STATUS "")

