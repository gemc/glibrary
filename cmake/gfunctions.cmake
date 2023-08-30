function(GLIBRARY_FETCH_IF_NOT_FOUND PACKAGE_TO_FIND)

    cmake_print_variables("${PACKAGE_TO_FIND}_FOUND")

    if (${PACKAGE_TO_FIND}_FOUND)
        message(STATUS "\n*** ${PACKAGE_TO_FIND} found ***")
        cmake_print_variables("${PACKAGE_TO_FIND}_VERSION")
        cmake_print_variables("${PACKAGE_TO_FIND}_INCLUDE_DIRS")
        cmake_print_variables("${PACKAGE_TO_FIND}_LIBRARIES")
        message(STATUS "")
    else ()
        message(STATUS "\n* ${PACKAGE_TO_FIND} not found, using FetchContent_MakeAvailable *")
        FetchContent_MakeAvailable(${PACKAGE_TO_FIND})
        message(STATUS "")
    endif ()

    message(STATUS "")

endfunction()


# Requiring that the build be out of source
function(REQUIRE_OUT_OF_SOURCE_BUILD)

    file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
    if (EXISTS "${LOC_PATH}")
        message(FATAL_ERROR "\nYou cannot build in a source directory (or any directory with a CMakeLists.txt file)\nPlease make a build subdirectory or use -B <build_dir> with cmake\n")
    endif ()

endfunction()


# Print all cmake variables
function(PRINT_ALL_VARIABLES)

    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(CMAKE Variable: "${_variableName} = ${${_variableName}}")
    endforeach ()

endfunction()


# Check if all dependencies are found
function(CHECK_GLIBRARY_DEPENDENCY LIBS)

    message( "\nChecking dependencies:\n")
    foreach (LIB ${LIBS})
        if (NOT ${LIB}_FOUND)
            message(FATAL_ERROR "\n${LIB} not found\n")
        else ()
            message(STATUS "${LIB} found")
        endif ()
    endforeach ()
   message("")

endfunction()
