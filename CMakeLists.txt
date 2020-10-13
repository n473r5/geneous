cmake_minimum_required(VERSION 3.1)

project(geneous CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(THIRD_PARTY_DIR ${CMAKE_BINARY_DIR}/third_party)
include_directories(${THIRD_PARTY_DIR}/include)
link_directories(${THIRD_PARTY_DIR}/lib)

add_library(geneous src/geneous-all.cc)
target_include_directories(geneous PUBLIC include/geneous)

if(BUILD_CLI)
	add_executable(geneous-cli src/geneous-cli)
	add_dependencies(geneous-cli geneous)
	target_link_libraries(geneous-cli geneous)
endif()

if(BUILD_TESTING)
	add_subdirectory(test)
endif()