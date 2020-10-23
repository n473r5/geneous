cmake_minimum_required(VERSION 3.1)

project(geneous)

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)
include_directories(${THIRD_PARTY_DIR}/include)
link_directories(${THIRD_PARTY_DIR}/lib)

add_subdirectory(core)

if(BUILD_CLI)
	add_subdirectory(cli)
endif()