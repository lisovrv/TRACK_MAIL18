cmake_minimum_required(VERSION 3.12)
project(Tree18)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS -fsanitize=address,leak)

add_executable(Tree18 main.cpp tree.cpp Akinator.cpp print_log.cpp)