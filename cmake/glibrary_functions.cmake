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