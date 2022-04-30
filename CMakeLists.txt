cmake_minimum_required(VERSION 3.22)
project(dsh C)

set(CMAKE_C_STANDARD 99)

add_executable(dsh main.c shell.c shell.h builtins.c builtins.h)
