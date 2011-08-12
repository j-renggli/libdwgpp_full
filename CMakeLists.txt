PROJECT(architect)

cmake_minimum_required(VERSION 2.6)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)

######## ALL DLLs ########

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(libredwgcpp)

######## SETUP ########

######## SOURCE CODE ########

INCLUDE_DIRECTORIES(.)

######## LINKER ########

LINK_LIBRARIES()

######## EXECUTABLE ########
