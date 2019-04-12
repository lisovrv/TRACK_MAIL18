cmake_minimum_required(VERSION 3.12)
project(My_Stack)

set(CMAKE_CXX_STANDARD 14)

add_executable(My_Stack stack.cpp stack.h print_log.cpp print_log.h main.cpp enum.h)