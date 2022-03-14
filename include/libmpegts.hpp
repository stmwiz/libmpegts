#pragma once

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define Q_DECL_EXPORT __declspec(dllexport)
#  define Q_DECL_IMPORT __declspec(dllimport)
#else
#  define Q_DECL_EXPORT     __attribute__((visibility("default")))
#  define Q_DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(LIBMPEGTS_LIBRARY)
#  define LIBMPEGTS_EXPORT Q_DECL_EXPORT
#else
#  define LIBMPEGTS_EXPORT Q_DECL_IMPORT
#endif

#include <cstdint>

constexpr int TS_H264 = 0;
constexpr int TS_H265 = 1;
constexpr int TS_AAC  = 2;
constexpr int TS_OPUS = 3;
constexpr int PACKET_SIZE=1316;

class LibmpegtsImpl;

class LIBMPEGTS_EXPORT Libmpegts
{
public:
    explicit Libmpegts();

    ~Libmpegts();

    uint8_t **encode(uint8_t *data,int32_t size,int64_t pts_us,int stream_type);
private:
    LibmpegtsImpl *impl;
};
