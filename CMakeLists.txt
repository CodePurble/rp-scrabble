cmake_minimum_required(VERSION 3.10)
project (rp-scrabble)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-DLOG_PATH=\"$(HOME)/RPDATA/Repos/scrabble/logs/\")
	add_definitions(-DDEBUG)
else()
	add_definitions(-DLOG_PATH=\"$(HOME)/.local/share/rp-scrabble/logs/\")
endif()

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cc")

include_directories(${INCLUDE_DIR})
add_executable(rp-scrabble ${SOURCE_FILES})
