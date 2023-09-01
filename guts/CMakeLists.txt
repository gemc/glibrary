cmake_minimum_required(VERSION 3.16...3.27)

project("guts"
        VERSION 1.0
        DESCRIPTION "Provides various utilities"
        LANGUAGES CXX)

set(LIB_NAME ${PROJECT_NAME})
set(EX_NAME ${PROJECT_NAME}_example)

# add target and set C++ standard
add_library(${LIB_NAME} SHARED)
add_executable(${EX_NAME})

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)
target_compile_features(${EX_NAME} PRIVATE cxx_std_20)

# add include directories, public so who depends on this library will also link to them
target_include_directories(${LIB_NAME} PRIVATE ${ALL_CLHEP_INCS})

# add link library with rpath, public so who depends on this library will also link to them
target_link_libraries(${EX_NAME} PRIVATE guts)
set_target_properties(${EX_NAME} PROPERTIES INSTALL_RPATH ${INSTALL_DIR}/lib)

# sources
target_sources(${LIB_NAME} PRIVATE
        gutilities.cc gutsConventions.cc)

# example
target_sources(${EX_NAME} PRIVATE
        example.cc)

install(TARGETS ${LIB_NAME} ${EX_NAME}
        LIBRARY DESTINATION ${INSTALL_DIR}/lib
        RUNTIME DESTINATION ${INSTALL_DIR}/bin
        INCLUDES DESTINATION ${INSTALL_DIR}/include
)

message(STATUS "Setting <${PROJECT_NAME}>")
