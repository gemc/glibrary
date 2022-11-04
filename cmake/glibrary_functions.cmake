include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL TRUE)

function(GLIBRARY_FETCH_IF_NOT_FOUND PACKAGE_TO_FIND)

    # cmake_print_variables("${PACKAGE_TO_FIND}_FOUND")

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

function(PRINT_ALL_VARIABLES)

    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(CMAKE Variable: "${_variableName} = ${${_variableName}}")
    endforeach()

endfunction()





function(CHECK_GLIBRARY_DEPS REQUEST)

    message(STATUS "Checking Dependencies for <${REQUEST}>")
    set(SOMETHING_MISSING FALSE)

    if(NOT CLHEP_FOUND)
        message(STATUS "CLHEP for <${REQUEST}>: ❌")
        set(SOMETHING_MISSING TRUE)
    endif()

    if(NOT XercesC_FOUND)
        message(STATUS "XercesC for <${REQUEST}>:  ❌")
        set(SOMETHING_MISSING TRUE)
    endif()

    if(NOT GEANT4_FOUND)
        message(STATUS "GEANT4 for <${REQUEST}>:  ❌")
        set(SOMETHING_MISSING TRUE)
    endif()

    if(SOMETHING_MISSING)
        message(STATUS "Some dependencies for <${REQUEST}> are not yet built.
   After they are built, re-run:
   \n\n\t cmake -S . -B <build_dir>
   \t cmake --build <build_dir> -j <ncpu>\n")
    endif()

endfunction()
