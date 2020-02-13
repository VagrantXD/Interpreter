cmake_minimum_required (VERSION 3.10)

set (PROJECT interpreter)
set (BIN ../bin)
set (CXX_STANDARD 17)
set (SRC_PATH "../src")

set (HEADERS 
    ${SRC_PATH}/expression.h
    ${SRC_PATH}/parser.h
    ${SRC_PATH}/token.h
) 

set (SOURCES
    ${SRC_PATH}/main.cpp
    ${SRC_PATH}/expression.cpp
    ${SRC_PATH}/parser.cpp
    ${SRC_PATH}/token.cpp
)

project (${PROJECT})

set (CMAKE_CXX_STANDARD ${CXX_STANDARD})
SET (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})

#add_executable (${PROJECT} ${HEADERS} ${SOURCES})
add_executable (${PROJECT} ${SOURCES})
