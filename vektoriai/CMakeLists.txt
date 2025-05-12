cmake_minimum_required(VERSION 4.0.0)
project(Studentu_programa_vector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB SOURCES "*.cpp")
add_executable(VectorProgram ${SOURCES})

#Test files
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)