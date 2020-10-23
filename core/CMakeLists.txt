project(geneous-core CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(geneous src/core.cc)
target_include_directories(geneous PRIVATE include/geneous PUBLIC include)

if(BUILD_TESTS OR BUILD_CORE_TESTS)
	add_subdirectory(test)
endif()