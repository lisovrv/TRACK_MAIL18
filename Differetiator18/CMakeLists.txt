cmake_minimum_required(VERSION 3.12)
project(Differentiator18)

set(CMAKE_CXX_STANDARD 14)

add_executable(Differentiator18 main.cpp Differentiator.cpp RDP_diff.cpp print_log.cpp tree.cpp
         Optimisator.cpp Printer_in_tex.cpp DSL.h commands.h)