cmake_minimum_required(VERSION 3.20)
project(prykhsof)
set(CMAKE_CPP_STANDARD 17 )
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>")
add_compile_options(-Wall -pedantic -Wno-long-long -Werror -Wmaybe-uninitialized)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(prykhsof_list progtest/prog06/list.cpp)
add_executable(phone_book progtest/prog06/phone_list.cpp)

