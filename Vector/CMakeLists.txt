cmake_minimum_required(VERSION 3.9.5)


add_executable(Vector_test test.cpp)

add_test(
	NAME Vector_test 
	COMMAND ${CMAKE_BINARY_DIR}/Vector/Vector_test
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Test
)
