add_executable(day04 day04.cpp)

target_link_libraries(day04 PRIVATE common)

target_include_directories(day04 PRIVATE ${PROJECT_SOURCE_DIR}/common)