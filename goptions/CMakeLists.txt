cmake_minimum_required(VERSION 3.16...3.27)

project("goptions"
        VERSION 1.0
        DESCRIPTION "Provides the glibrary"
        LANGUAGES CXX)

set(LIB_NAME ${PROJECT_NAME})
set(EX_NAME1 ${PROJECT_NAME}_example_simple)
set(EX_NAME2 ${PROJECT_NAME}_example_structured)
set(EX_NAME3 ${PROJECT_NAME}_example_cumulativeStructured)

# add target and set C++ standard
add_library(${LIB_NAME} SHARED)
#add_executable(${EX_NAME1}, ${EX_NAME2}, ${EX_NAME3})
add_executable(${EX_NAME1})
add_executable(${EX_NAME2})
add_executable(${EX_NAME3})

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)
target_compile_features(${EX_NAME1} PRIVATE cxx_std_20)
target_compile_features(${EX_NAME2} PRIVATE cxx_std_20)
target_compile_features(${EX_NAME3} PRIVATE cxx_std_20)


# add include directories, public so who depends on this library will also link to them
target_include_directories(${LIB_NAME} PRIVATE ${ALL_CLHEP_INCS} ${GLIBRARIES_INC_DIRS})
target_include_directories(${EX_NAME1} PRIVATE ${ALL_CLHEP_INCS} ${GLIBRARIES_INC_DIRS})
target_include_directories(${EX_NAME2} PRIVATE ${ALL_CLHEP_INCS} ${GLIBRARIES_INC_DIRS})
target_include_directories(${EX_NAME3} PRIVATE ${ALL_CLHEP_INCS} ${GLIBRARIES_INC_DIRS})

# add link library, public so who depends on this library will also link to them
target_link_libraries(${LIB_NAME} PRIVATE guts)
# add link library with rpath, public so who depends on this library will also link to them
target_link_libraries(${EX_NAME1} PRIVATE guts goptions)
target_link_libraries(${EX_NAME2} PRIVATE guts goptions)
target_link_libraries(${EX_NAME3} PRIVATE guts goptions)
set_target_properties(${EX_NAME1} PROPERTIES INSTALL_RPATH ${INSTALL_DIR}/lib)
set_target_properties(${EX_NAME2} PROPERTIES INSTALL_RPATH ${INSTALL_DIR}/lib)
set_target_properties(${EX_NAME3} PROPERTIES INSTALL_RPATH ${INSTALL_DIR}/lib)

# sources
target_sources(${PROJECT_NAME} PRIVATE
        goption.cc goptions.cc)

target_sources(${EX_NAME1} PRIVATE
        examples/simpleExample.cc)
target_sources(${EX_NAME2} PRIVATE
        examples/structuredExample.cc)
target_sources(${EX_NAME3} PRIVATE
        examples/cumulativeStructuredExample.cc)

install(TARGETS ${LIB_NAME} ${EX_NAME1} ${EX_NAME2} ${EX_NAME3}
        LIBRARY DESTINATION ${INSTALL_DIR}/lib
        RUNTIME DESTINATION ${INSTALL_DIR}/bin
        INCLUDES DESTINATION ${INSTALL_DIR}/include
)

message(STATUS "Setting <${PROJECT_NAME}>")
