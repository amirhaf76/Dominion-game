cmake_minimum_required(VERSION 3.12)
project(Domination_game C)

set(CMAKE_C_STANDARD 99)

add_executable(Domination_game main.c dominion.h dominion.c)
add_executable(Test_Domination_game test_different_part_of_program.c)
