include(FetchContent)
include(CMakePrintHelpers) # to print variables with cmake_print_variables
set(PACKAGE_TO_FIND "Geant4")

FetchContent_Declare(
        ${PACKAGE_TO_FIND}
        GIT_REPOSITORY https://github.com/Geant4/geant4
        GIT_TAG v11.0.3
        SOURCE_DIR   ${CMAKE_BINARY_DIR}/Geant4
        CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=${Geant4_INSTALL_DIR}
                    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                    -DGEANT4_USE_GDML=ON
                    -DXercesC_LIBRARY=${XercesC_LIBRARY}
                    -DXercesC_INCLUDE_DIR=${XercesC_INCLUDE_DIR}
                    -DCLHEP_ROOT_DIR=${CLHEP_ROOT_DIR}
                    -DGEANT4_USE_QT=ON
                    -DGEANT4_INSTALL_DATA=ON
                    -DGEANT4_USE_SYSTEM_EXPAT=OFF
                    -DGEANT4_INSTALL_EXAMPLES=OFF
                    -DGEANT4_USE_QT=ON
        BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
)


find_package(Geant4 QUIET COMPONENTS vis_all ui_all qt gdml)
# TODO: FetchContent_MakeAvailable does not work
if(Geant4_FOUND)
    message(STATUS "\n*** ${PACKAGE_TO_FIND} found ***")
    cmake_print_variables(Geant4_VERSION)
    cmake_print_variables(Geant4_DIR)
    cmake_print_variables(Geant4_LIBRARIES)
    message(STATUS "")
else()
    message(STATUS "\n")
    message(STATUS "\n* Fetching and configuring ${PACKAGE_TO_FIND} *")
    #FetchContent_MakeAvailable(Geant4)
    # cmake_print_variables(XercesC_LIBRARY)
    # cmake_print_variables(XercesC_INCLUDE_DIR)

    #add_dependencies(Geant4 CLHEP)
    #add_dependencies(Geant4 xercesc)
    message(STATUS "")
endif()

cmake_print_variables(Geant4_INCLUDE_DIR)
cmake_print_variables(Geant4_LIBRARIES)
cmake_print_variables(Geant4_DATASETS)
message(STATUS "")

