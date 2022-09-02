cmake_minimum_required(VERSION 3.21)
project(prykhsof)
set(CMAKE_CPP_STANDARD 17 )
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
add_compile_options(-Wall -pedantic -Wno-long-long -Werror)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(prosem1 other/prosem/sem01/stream1.cpp)
add_executable(prosem2 other/prosem/sem02/07_inf.c)