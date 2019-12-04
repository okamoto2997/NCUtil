cmake_minimum_required(VERSION 3.9.5)


add_executable(Utility_test test.cpp)

add_test(
 NAME Utility_test 
 COMMAND ${CMAKE_BINARY_DIR}/Utility/Utility_test
 WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Test
)
