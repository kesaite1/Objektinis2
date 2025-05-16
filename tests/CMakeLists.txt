add_executable(Tests
    student_test.cpp
)

target_include_directories(Tests PRIVATE
    ${CMAKE_SOURCE_DIR}/vektoriai
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Tests StudentLib)

add_test(NAME AllTests COMMAND Tests)