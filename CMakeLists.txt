cmake_minimum_required(VERSION 3.14)

project(libmpegts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE NATIVE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE NATIVE_MUXER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/muxer/*)
#file(GLOB_RECURSE NATIVE_DEMUXER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/demuxer/*)

add_library(${PROJECT_NAME} SHARED
    libmpegts.cpp
    ${NATIVE_SOURCE}
    ${NATIVE_MUXER_SOURCE}
)

target_compile_definitions(${PROJECT_NAME}  PRIVATE LIBMPEGTS_LIBRARY)

add_subdirectory(test)
