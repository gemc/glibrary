include(FetchContent)
include(CMakePrintHelpers) # to print variables with cmake_print_variables

 FetchContent_Declare(
         CLHEP
         GIT_REPOSITORY https://gitlab.cern.ch/CLHEP/CLHEP.git
         GIT_TAG CLHEP_2_4_5_1
 )

find_package(CLHEP 2.4.5.1 REQUIRED)

if(CLHEP_FOUND)
    message(STATUS "")
    message(STATUS "* A local install of CLHEP was found - using it*")
    message(STATUS "")
else()
    message(STATUS "")
    message(STATUS "* CLHEP was not found - Fetching and installing it *")
   # FetchContent_MakeAvailable(CLHEP)
    message(STATUS "")
endif()

cmake_print_variables(CLHEP_INCLUDE_DIRS)
cmake_print_variables(CLHEP_LIBRARIES)

