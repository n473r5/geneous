include(ExternalProject)

ExternalProject_Add(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.10.0
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}
	UPDATE_COMMAND ""
)

add_executable(tests matrix_tests.cc vector_tests.cc)
add_dependencies(tests geneous googletest)
target_link_libraries(tests geneous gtest_main gtest gmock)