cmake_minimum_required(VERSION 3.20)
project(libmar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit and integration tests" ON)

add_subdirectory(src)
add_subdirectory(examples)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
 
