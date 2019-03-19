cmake_minimum_required(VERSION 3.13)
project(circuits_sim C)

set(CMAKE_C_STANDARD 11)

add_executable(circuits_sim src/main.c src/linkedList/include/linkedList.h src/linkedList/linkedList.c src/circuits/include/circuitsSim.h src/circuits/circuitsSim.c)