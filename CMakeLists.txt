cmake_minimum_required(VERSION 2.6)
project(vpl1)

add_executable(vpl1 main.cpp)

install(TARGETS vpl1 RUNTIME DESTINATION bin)
