cmake_minimum_required(VERSION 3.20)
project(prykhsof)
set(CMAKE_CXX_STANDARD 20 )
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
add_compile_options(-Wall -pedantic -Wno-long-long -Werror)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(prog03_bells progtest/prog03/bells2.cpp)
add_executable(prog03_working_days progtest/prog03/working_days_counter.cpp)
