PROJECT(Bamboo_III_Analysis)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE (FindROOT.cmake)

# set the include directories
INCLUDE_DIRECTORIES(${ROOT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

#remove root gui library
LIST (REMOVE_ITEM ROOT_LIBRARIES "-lGui")

LINK_DIRECTORIES (${ROOT_LIBRARY_DIR})

# rpath setting for installation
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# std=c++0x
SET(CMAKE_CXX_FLAGS "-std=c++0x -g")

# link with root
# target selector from bamboo_ii
#ADD_EXECUTABLE(selector selector.C DepositionSelector.C EnergyDeposition.C)
#TARGET_LINK_LIBRARIES (selector ${ROOT_LIBRARIES})

# target flux_analysis to analyze the angular distribution and
# energy distribution of flux

ADD_EXECUTABLE(flux_analysis flux.C FluxSelector.C)
TARGET_LINK_LIBRARIES (flux_analysis ${ROOT_LIBRARIES})
INSTALL(TARGETS flux_analysis DESTINATION bin)

ADD_EXECUTABLE(pea_cuboid pea_cuboid.C PEASelector.C)
TARGET_LINK_LIBRARIES (pea_cuboid ${ROOT_LIBRARIES})
INSTALL(TARGETS pea_cuboid DESTINATION bin)

ADD_EXECUTABLE(simpleSelector simpleSelector.C SimpleEnergyData.cc SimpleEnergyDepositionSelector.C)
TARGET_LINK_LIBRARIES (simpleSelector ${ROOT_LIBRARIES})
INSTALL(TARGETS simpleSelector DESTINATION bin)

ADD_EXECUTABLE(smearSelection smearSelection.C)
TARGET_LINK_LIBRARIES (smearSelection ${ROOT_LIBRARIES})
INSTALL(TARGETS smearSelection DESTINATION bin)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

