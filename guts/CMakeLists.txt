cmake_minimum_required(VERSION 3.16...3.27)

project("guts"
        VERSION 1.0
        DESCRIPTION "Provides the gutilities library"
        LANGUAGES CXX)

# add target and set C++ standard
add_library(${PROJECT_NAME} SHARED)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# add include directories, public so who depends on this library will also link to them
target_include_directories(${PROJECT_NAME} PUBLIC ${ALL_CLHEP_INCS})




# sources
target_sources(${PROJECT_NAME} PRIVATE
        gutilities.cc gutsConventions.cc)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION  ${INSTALL_DIR}/lib
        INCLUDES DESTINATION ${INSTALL_DIR}/include
)

message(STATUS "Setting <${PROJECT_NAME}>")
