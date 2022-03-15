cmake_minimum_required(VERSION 3.14)

project(test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

foreach(BIN_NAME test_aac_avc)
    add_executable(${BIN_NAME} ${BIN_NAME}.cpp)
    target_link_libraries(${BIN_NAME} PRIVATE libmpegts)
    target_compile_definitions(${BIN_NAME} PRIVATE
        IN_AUDIO_RES_PATH="${CMAKE_SOURCE_DIR}/res/audio.aac"
        IN_VIDEO_RES_PATH="${CMAKE_SOURCE_DIR}/res/video.h264"
        OUT_TS_RES_PATH="${CMAKE_CURRENT_BINARY_DIR}/av.ts")
endforeach(BIN_NAME)
