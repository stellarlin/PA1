cmake_minimum_required(VERSION 3.20)
project(prykhsof)
set(CMAKE_CXX_STANDARD 14 )
add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++14>")
add_compile_options(-Wall -pedantic -Wno-long-long -Werror)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# add_executable(prykhsof_OTH other)

