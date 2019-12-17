# VPL1 SRC

set(SRC_BASE rangesensor.cpp vpfilereader.cpp viewstructure.cpp pmutils.cpp vptriangle.cpp vpvertex.cpp vplutils.cpp vprobot.cpp)
set(SRC_ROBOTS vprfreeflyer.cpp)

#set(SRC_STRUCTURES coctreevpl.cpp)
#set(SRC_PARTIAL_MODEL partialmodelbase.cpp pmvolumetric.cpp pmvoctree.cpp pmvoctreeig.cpp pmvoctreeigkriegel12.cpp pmvoctreevasquez09.cpp pmvorearsidevoxel.cpp)
#set(SRC_VIEW viewstructure.cpp vpfilereader.cpp pmutils.cpp vptriangle.cpp vpvertex.cpp)
#set(SRC_OTHER evaluationresult.cpp viewsynthesis.cpp)
#set(SRC_ALL ${SRC_PARTIAL_MODEL} ${SRC_VIEW} ${SRC_OTHER} ${SRC_STRUCTURES})
set(SRC_ALL ${SRC_BASE} ${SRC_ROBOTS})


#----------------------------- BOOST --------------------
#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories( ${Boost_INCLUDE_DIR} )


# -------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VPL1_SOURCE_DIR}/lib)
add_library(vpl1 SHARED ${SRC_ALL})

# We need this directory, and users of our library will need it too
target_include_directories(vpl1 PUBLIC ${VPL1_SOURCE_DIR}/include)

target_link_libraries(vpl1 ${LIBS_OCTOMAP})


# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

