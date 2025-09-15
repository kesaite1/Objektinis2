cmake_minimum_required(VERSION 4.0.0)

project(Studentu_programa)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dll)
add_subdirectory(vektoriai)
add_subdirectory(tests)


enable_testing()