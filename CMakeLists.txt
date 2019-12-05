cmake_minimum_required(VERSION 2.6)

### VIEW PLANNING LIBRARY ###
project(VPL1)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set this as false if you do not want the app examples (under development)
set(BUILD_APPS true)


# Configure the path to the octomap library
set(OCTOMAP_LIB_PATH /home/irving/projects/octomap/lib)
set(OCTOMAP_INCLUDE_PATH /home/irving/projects/octomap/octomap/include)

# ----------------------------- Octomap --------------------
#set(OCTOMAP_DIR ${VPL_SOURCE_DIR}/../octomap-devel) ## Needs configuration
include_directories(${OCTOMAP_INCLUDE_PATH})
link_directories(${OCTOMAP_LIB_PATH})
set(LIBS_OCTOMAP octomap octomath)

add_subdirectory(src)

if(BUILD_APPS)
   add_subdirectory(apps)
endif()

