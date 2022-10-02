cmake_minimum_required(VERSION 3.21)
project(prykhsof)
set(CMAKE_CPP_STANDARD 17 )
add_compile_options(-Wall -pedantic -Wno-long-long -Werror)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(cvik1_first other/lessons/cv01/first_code.cpp)

add_executable(cvik2_calk other/lessons/cv02/calk.cpp)
add_executable(cvik2_minmax other/lessons/cv02/minmax.cpp)
add_executable(cvik2_time other/lessons/cv02/time.cpp)

add_executable(cvik3_2D other/lessons/cv03/2D.cpp)
add_executable(cvik3_3D other/lessons/cv03/3D.cpp)
add_executable(cvik3_teplota other/lessons/cv03/teplota.cpp)
add_executable(cvik3_equation other/lessons/cv03/equation_two.cpp)
add_executable(cvik3_cool_calk other/lessons/cv03/cool_calk.cpp)

add_executable(cvik4_odd_number other/lessons/cv04/odd_number.cpp)
add_executable(cvik4_sort_num other/lessons/cv04/sort_of_numbers.cpp)
add_executable(cvik4_week other/lessons/cv04/week.cpp)
add_executable(cvik4_year other/lessons/cv04/year.cpp)
add_executable(cvik4_triangle other/lessons/cv04/triangle.cpp)
add_executable(cvik4_KNP other/lessons/cv04/KNP.cpp)
add_executable(cvik4_rovnice other/lessons/cv04/rovnice.cpp)
add_executable(cvik4_numbers_to_words other/lessons/cv04/numbers_to_words.cpp)
add_executable(cvik4_datum other/lessons/cv04/datum.cpp)

add_executable(cvik5_arrayStat other/lessons/cv05/arrayStat.cpp)