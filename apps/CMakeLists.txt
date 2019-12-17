# VPL1 apps

cmake_minimum_required(VERSION 2.6)

project(apps)

# Octomap
#include_directories(${OCTOMAP_INCLUDE_PATH})
#link_directories(${OCTOMAP_LIB_PATH})
#set(LIBS_OCTOMAP octomap octomath)

#--------------- VPL ------------
include_directories(${VPL1_SOURCE_DIR}/include)
link_directories(${VPL1_SOURCE_DIR}/lib)
set(LIB_VPL1 vpl1)

message("Building vpl apps")

# Programs
add_executable(check_octomap check_octomap.cpp)
target_link_libraries(check_octomap ${LIBS_OCTOMAP} ${LIB_VPL1})


add_executable(check_range_sensor check_range_sensor.cpp)
target_link_libraries(check_range_sensor ${LIBS_OCTOMAP} ${LIB_VPL1})


add_executable(check_freeflyer check_freeflyer.cpp)
target_link_libraries(check_freeflyer ${LIBS_OCTOMAP} ${LIB_VPL1})














