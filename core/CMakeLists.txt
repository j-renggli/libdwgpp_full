PROJECT(core)

cmake_minimum_required(VERSION 2.6)

######## SETUP ########

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -O -ansi -pedantic -g -pg -Wno-long-long -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -ansi -pedantic -g -pg  -Wno-long-long")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)

######## SOURCE CODE ########

INCLUDE_DIRECTORIES(.)

SET(CORE_SRC
src/iobuffer.cpp
src/resultcode.cpp
src/string.cpp

src/buffers/filebuffer.cpp
src/buffers/membuffer.cpp
src/buffers/tempfilebuffer.cpp
src/buffers/volatilebuffer.cpp

src/log/coutdisplay.cpp
src/log/logmanager.cpp
src/log/simplefiledisplay.cpp

src/random/lincong.cpp
src/random/random.cpp
)

######## LINKER ########

LINK_LIBRARIES(
boost_filesystem-mt
boost_system-mt
boost_thread-mt
icuio
)

######## LIBRARIES ########

ADD_LIBRARY(core SHARED ${CORE_SRC})
