cmake_minimum_required(VERSION 4.0.0)
project(Studentu_programa_vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
file(GLOB SOURCES "*.cpp")

add_executable(VectorProgram ${SOURCES})