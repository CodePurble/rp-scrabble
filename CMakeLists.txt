cmake_minimum_required(VERSION 3.10)
project (rp-scrabble)

# Setup OpenGL and GLFW3
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW3 REQUIRED glfw3)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GLFW3_CFLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GLFW3_CFLAGS} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GLFW3_CFLAGS} -Wall")
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DLOG_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/logs/\")
    add_definitions(-DWORDLIST=\"${CMAKE_CURRENT_SOURCE_DIR}/assets/twl06_wordlist.txt\")
    add_definitions(-DLAYOUT=\"${CMAKE_CURRENT_SOURCE_DIR}/assets/layout.ini\")
    add_definitions(-DDEBUG)
else()
    add_definitions(-DWORDLIST=\"$(HOME)/.local/share/rp-scrabble/assets/twl06_wordlist.txt\")
    add_definitions(-DLAYOUT=\"$(HOME)/.local/share/rp-scrabble/assets/layout.ini\")
    add_definitions(-DLOG_PATH=\"$(HOME)/.local/share/rp-scrabble/logs/\")
endif()

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${IMGUI_DIR}/*.cpp")

include_directories(${INCLUDE_DIR} ${IMGUI_DIR} ${GLFW3_INCLUDE_DIRS})
add_executable(rp-scrabble ${SOURCE_FILES})
target_link_libraries(rp-scrabble ${GLFW3_LIBRARIES} GL)
set_target_properties(rp-scrabble PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
install(TARGETS rp-scrabble DESTINATION bin)
