include(CMakePrintHelpers) # to print variables with cmake_print_variables

function(GLIBRARY_FIND_PACKAGE PACKAGE_TO_FIND)

    find_package(${PACKAGE_TO_FIND} QUIET)
    cmake_print_variables("${PACKAGE_TO_FIND}_FOUND")

    if(${PACKAGE_TO_FIND}_FOUND)
        message(STATUS "\n*** ${PACKAGE_TO_FIND} found ***")
        cmake_print_variables("${PACKAGE_TO_FIND}_VERSION")
        cmake_print_variables("${PACKAGE_TO_FIND}_INCLUDE_DIRS")
        cmake_print_variables("${PACKAGE_TO_FIND}_LIBRARIES")
        message(STATUS "")
    else()
        message(STATUS "\n* ${PACKAGE_TO_FIND} not found, using FetchContent_MakeAvailable *")
        FetchContent_MakeAvailable(${PACKAGE_TO_FIND})
        message(STATUS "")
    endif()

    message(STATUS "")

endfunction()

function(REQUIRE_OUT_OF_SOURCE_BUILD)

    file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
    if(EXISTS "${LOC_PATH}")
        message(FATAL_ERROR "\nYou cannot build in a source directory (or any directory with a CMakeLists.txt file)\nPlease make a build subdirectory or use -B <build_dir> with cmake\n")
    endif()

endfunction()

