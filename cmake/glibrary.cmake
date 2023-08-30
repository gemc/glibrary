include(CMakePrintHelpers)                  # to print variables with cmake_print_variables
set(CMAKE_FIND_PACKAGE_TARGETS_GLOBAL TRUE) # Promotes all IMPORTED targets discovered by  find_package() to a GLOBAL scope

option(PRINT_ALL_VARS "Print all cmake variables" OFF)
option(RUN_TESTS      "Compile and run the tests" OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(GLIBRARY_ROOT "${PROJECT_SOURCE_DIR}")

if (RUN_TESTS)
    include(CTest)
    add_subdirectory(tests)
    message("Tests are ON")
    message(Compiling " ${CMAKE_PROJECT_NAME} ")

endif ()

###  dependencies
include(clhep)
include(geant4)
include(gfunctions)


# make sure we're not in the source directory
require_out_of_source_build()

if (PRINT_ALL_VARS)
    print_all_variables()
endif ()

set(INSTALL_DIR "${GLIBRARY_ROOT}/install")

set(GLIBRARIES_INC_DIRS
        ${GLIBRARY_ROOT}/eventDispenser
        ${GLIBRARY_ROOT}/g4system
        ${GLIBRARY_ROOT}/gQtButtonsWidget
        ${GLIBRARY_ROOT}/g4display
        ${GLIBRARY_ROOT}/gdata
        ${GLIBRARY_ROOT}/gdynamicDigitization
        ${GLIBRARY_ROOT}/gfactory
        ${GLIBRARY_ROOT}/gfields
        ${GLIBRARY_ROOT}/ghit
        ${GLIBRARY_ROOT}/goptions
        ${GLIBRARY_ROOT}/gparticle
        ${GLIBRARY_ROOT}/gsplash
        ${GLIBRARY_ROOT}/gstreamer
        ${GLIBRARY_ROOT}/gsystem
        ${GLIBRARY_ROOT}/gtouchable
        ${GLIBRARY_ROOT}/gtranslationTable
        ${GLIBRARY_ROOT}/guts
        ${GLIBRARY_ROOT}/textProgressBar
)

set(ALL_CLHEP_INCS ${CLHEP_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/clhep-build)
