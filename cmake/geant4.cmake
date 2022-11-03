include(FetchContent)
include(glibrary_functions)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND Geant4)

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://github.com/Geant4/geant4
        GIT_TAG v11.0.3
        SOURCE_DIR ${CMAKE_BINARY_DIR}/geant4-source
        BINARY_DIR ${CMAKE_BINARY_DIR}/geant4-build
        CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=${SOURCE_DIR}
                    -DGEANT4_USE_GDML=ON
                    -DXercesC_LIBRARY=${XercesC_LIBRARY}
                    -DXercesC_INCLUDE_DIR=${XercesC_INCLUDE_DIR}
                    -DCLHEP_ROOT_DIR=${CLHEP_ROOT_DIR}
                    -DGEANT4_USE_QT=ON
                    -DGEANT4_INSTALL_DATA=ON
                    -DGEANT4_USE_SYSTEM_EXPAT=OFF
                    -DGEANT4_INSTALL_EXAMPLES=OFF
                    -DGEANT4_USE_QT=ON
        #BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
)



GLIBRARY_FIND_PACKAGE(${PACKAGE_TO_FIND})

