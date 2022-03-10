cmake_minimum_required(VERSION 3.14)

project(libmpegts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE NATIVE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(libmpegts SHARED
    ${NATIVE_SOURCE}
)

target_compile_definitions(libmpegts PRIVATE LIBMPEGTS_LIBRARY)
