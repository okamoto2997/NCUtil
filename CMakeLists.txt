cmake_minimum_required(VERSION 3.9.5)

set(CMAKE_CXX_COMPILER g++)
enable_testing()

project(NCUtils CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pipe -std=c++2a")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -mtune=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -pg")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Test)
add_subdirectory(Log)

