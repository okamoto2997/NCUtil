cmake_minimum_required(VERSION 3.9.5)


add_executable(Geometry_test test.cpp)

add_test(
	NAME Geometry_test
	COMMAND ${CMAKE_BINARY_DIR}/Geometry/Geometry_test
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Test
)
