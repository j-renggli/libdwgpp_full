PROJECT(testing)

cmake_minimum_required(VERSION 2.6)

######## SETUP ########

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -O -ansi -pedantic -g -pg -Wno-long-long -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -ansi -pedantic -g -pg -Wno-long-long")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

######## SOURCE CODE ########

INCLUDE_DIRECTORIES(. ..)

SET(SUITES_SRC

)

SET(UTILS_SRC
testing.cpp

suite/dwgbuffer.cpp

utils/unittestsuite.cpp
)

######## LINKER ########

SET(UTILS_LIB
boost_program_options
#icuio

core
libredwgpp
)

LINK_LIBRARIES(${UTILS_LIB})

######## EXECUTABLE ########

ADD_EXECUTABLE(testing ${UTILS_SRC} ${SUITES_SRC})
