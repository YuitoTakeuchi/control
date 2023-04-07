cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME LQRSolverExample)
project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STNDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(example)