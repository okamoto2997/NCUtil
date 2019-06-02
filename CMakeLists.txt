cmake_minimum_required(VERSION 3.9.5)

set(CMAKE_CXX_COMPILER g++)
enable_testing()
enable_language(CXX)

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(NCUtils)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pipe")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -mtune=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -pg")

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Test)
add_subdirectory(Log)
add_subdirectory(Utility)
add_subdirectory(Vector)

