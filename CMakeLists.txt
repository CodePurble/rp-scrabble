cmake_minimum_required(VERSION 3.10)
project (rp-scrabble)

# Ref: https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lX11 -lGL -lpthread -lpng -lstdc++fs")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -lX11 -lGL -lpthread -lpng -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -lX11 -lGL -lpthread -lpng -lstdc++fs")
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HOME_DIR $ENV{HOME})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DLOG_PATH=\"${HOME_DIR}/RPDATA/Repos/rp-scrabble/logs/\")
    add_definitions(-DDEBUG)
else()
    add_definitions(-DLOG_PATH=\"${HOME_DIR}/.local/share/rp-scrabble/logs/\")
endif()

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cc")

include_directories(${INCLUDE_DIR})
add_executable(rp-scrabble ${SOURCE_FILES})
