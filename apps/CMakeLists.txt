# VPL1 apps

cmake_minimum_required(VERSION 2.6)

project(apps)

# Octomap
#include_directories(${OCTOMAP_INCLUDE_PATH})
#link_directories(${OCTOMAP_LIB_PATH})
#set(LIBS_OCTOMAP octomap octomath)

message("Building vpl apps")

# Programs
add_executable(check_octomap check_octomap.cpp)
target_link_libraries(check_octomap ${LIBS_OCTOMAP})















