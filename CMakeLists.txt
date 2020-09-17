cmake_minimum_required(VERSION 3.1)

project(geneous)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/third_party)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

ExternalProject_Add(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(include/geneous)
add_library(geneous src/geneous-all.cc)

add_executable(tests test/matrix_tests.cc test/vector_tests.cc)
add_dependencies(tests googletest)
target_link_libraries(tests gtest gtest_main pthread)