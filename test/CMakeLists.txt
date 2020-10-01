include(ExternalProject)

ExternalProject_Add(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}
)

add_executable(tests matrix_tests.cc vector_tests.cc)
add_dependencies(tests geneous googletest)
target_link_libraries(tests geneous)

if(WIN32)
	set(gtest_disable_pthreads ON)
	target_link_libraries(tests gtest_main gtest gmock)
else()
	target_link_libraries(tests gtest_main gtest gmock pthread)
endif()