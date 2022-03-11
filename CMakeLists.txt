cmake_minimum_required(VERSION 3.14)

project(libmpegts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE NATIVE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(${PROJECT_NAME} SHARED
    libmpegts.cpp
    ${NATIVE_SOURCE}
)

target_compile_definitions(${PROJECT_NAME}  PRIVATE LIBMPEGTS_LIBRARY)
