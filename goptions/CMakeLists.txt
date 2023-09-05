cmake_minimum_required(VERSION 3.16...3.27)

project("goptions"
        VERSION 1.0
        DESCRIPTION "Provides the glibrary"
        LANGUAGES CXX)

set(LIB_NAME ${PROJECT_NAME})
set(EXE_NAMES "simple;structured;cumulative_structured")

# add library and executables targets and set C++ standard
add_library(${LIB_NAME} SHARED)
add_executables("${EXE_NAMES}")
set_targets_compile_features("${LIB_NAME};${EXE_NAMES}" cxx_std_20)

# add include directories, public (private for now, check later) so who depends on this library will also link to them
set_targets_include_directories("${LIB_NAME};${EXE_NAMES}" "${ALL_CLHEP_INCS};${GLIBRARIES_INC_DIRS}")

# add link library, public so who depends on this library will also link to them
target_link_libraries(${LIB_NAME} PRIVATE guts)
set_targets_link_libraries("${EXE_NAMES}" "guts;goptions")

# add link library with rpath, public so who depends on this library will also link to them
set_targets_rpaths("${EXE_NAMES}" "${INSTALL_DIR}/lib")

# sources
target_sources(${PROJECT_NAME} PRIVATE
        goption.cc goptions.cc)

set_target_sources("${EXE_NAMES}")


install(TARGETS ${LIB_NAME} ${EXE_NAMES}
        LIBRARY DESTINATION ${INSTALL_DIR}/lib
        RUNTIME DESTINATION ${INSTALL_DIR}/bin
        INCLUDES DESTINATION ${INSTALL_DIR}/include
)

message(STATUS "Setting <${PROJECT_NAME}>")
