cmake_minimum_required(VERSION 3.14)
project(anagrama C)

set(CMAKE_C_STANDARD 99)

add_executable(anagrama main.c anagrama_bintree.c)