add_library(skaiciavimas SHARED skaiciavimas.cpp)

target_include_directories(skaiciavimas PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(skaiciavimas PROPERTIES OUTPUT_NAME "skaiciavimas")
