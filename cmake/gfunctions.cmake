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
    message("\nChecking dependencies:\n")
    foreach (LIB ${LIBS})
        if (NOT ${LIB}_FOUND)
            message(FATAL_ERROR "\n${LIB} not found\n")
        else ()
            message(STATUS "${LIB} found")
        endif ()
    endforeach ()
    message("")
endfunction()


# set target_compile_features for all targets
function(SET_TARGETS_COMPILE_FEATURES TARGETS FEATURE)
    foreach (TARGET ${TARGETS})
        message(STATUS "Adding target_compile_features: ${TARGET} with ${FEATURE}")
        target_compile_features(${TARGET} PUBLIC ${FEATURE})
    endforeach ()
    message("")
endfunction()


# add multiple executables
function(ADD_EXECUTABLES TARGETS)
    message(STATUS "Adding executables: ${TARGETS}")
    foreach (TARGET ${TARGETS})
        add_executable(${TARGET})
    endforeach ()
    message("")
endfunction()


# target_sources. It assumes the source file has the same name and .cc extension AND it's inside the examples directory
function(SET_TARGET_SOURCES TARGETS)
    message(STATUS "Adding target_sources: ${TARGETS}")
    foreach (TARGET ${TARGETS})
        #message(STATUS "Adding target_sources: examples/${TARGET}")
        target_sources(${TARGET} PRIVATE "examples/${TARGET}.cc")
    endforeach ()
    message("")
endfunction()


# add target_link_libraries for all targets
function(SET_TARGETS_LINK_LIBRARIES TARGETS LIBRARIES)
    message(STATUS "Adding target_link_libraries: ${TARGETS} with ${LIBRARIES}")
    foreach (TARGET ${TARGETS})
        #message(STATUS "Adding target_link_libraries: ${TARGET} with ${LIBRARIES}")
        target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
    endforeach ()
    message("")
endfunction()


# add target_include_directories for all targets
function(SET_TARGETS_INCLUDE_DIRECTORIES TARGETS INCLUDE_DIRS)
    message(STATUS "Adding target_include_directories: ${TARGETS} with ${INCLUDE_DIRS}")
    foreach (TARGET ${TARGETS})
        target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
    endforeach ()
    message("")
endfunction()


# set rpath for all targets
function(SET_TARGETS_RPATHS TARGETS RPATH_DIR)
    message(STATUS "Adding rpath for ${TARGETS} to ${RPATH_DIR}")
    foreach (TARGET ${TARGETS})
        set_target_properties(${TARGET} PROPERTIES INSTALL_RPATH ${RPATH_DIR})
    endforeach ()
    message("")
endfunction()
