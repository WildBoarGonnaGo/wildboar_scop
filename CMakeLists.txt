cmake_minimum_required(VERSION 3.20)
project(wildboar_scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
add_compile_options(-g)

add_executable(wildboar_scop train/InterleavedArray.c)
target_link_libraries(wildboar_scop -lglut -lGL -lX11 -lpthread -lXrandr -lXi -ldl)
