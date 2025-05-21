project(Studentu_programa_vector)

add_library(StudentLib
    students.cpp
    functions.cpp
)

target_include_directories(StudentLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(VectorProgram vektoriuMain.cpp)

target_link_libraries(VectorProgram StudentLib)

add_custom_command(TARGET VectorProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:skaiciavimas>
        $<TARGET_FILE_DIR:VectorProgram>)
