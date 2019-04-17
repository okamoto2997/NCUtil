cmake_minimum_required(VERSION 3.9.5)


add_executable(Log_test test.cpp)

add_test(
 NAME Log_test 
 COMMAND ${CMAKE_BINARY_DIR}/Log/Log_test
 WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Test
)
