PROJECT(Bamboo_II_Analysis)

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
ADD_EXECUTABLE(selector selector.C DepositionSelector.C EnergyDeposition.C)
TARGET_LINK_LIBRARIES (selector ${ROOT_LIBRARIES})
