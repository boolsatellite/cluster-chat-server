cmake_minimum_required(VERSION 3.22)
project(chat)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH {${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/serverr)

add_subdirectory(src)