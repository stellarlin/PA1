cmake_minimum_required(VERSION 3.20)
project(prykhsof)
set(CMAKE_CXX_STANDARD 17 )
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
add_compile_options(-Wall -pedantic -Wno-long-long -Werror)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

 add_executable(pr1_bank progtest/prog01/bankovni_ucet.cpp)
add_executable(pr1_ABC progtest/prog01/ABC.cpp)
