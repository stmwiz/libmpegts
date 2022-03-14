#include <vector>
#include <memory.h>

#include "libmpegts.hpp"
#include "src/muxer/ts_muxer.hpp"

class LibmpegtsImpl {
    static const int PACKET_NUM = 1024 * 8;
public:
    explicit LibmpegtsImpl(){
        ts = new MpegTsMuxer::TsMuxer();
        buffers = new uint8_t*[PACKET_NUM];
        buffer = new uint8_t[PACKET_SIZE * PACKET_NUM];
        buffer_offset = 0;
    }

    ~LibmpegtsImpl(){
        delete [] buffer;
        delete [] buffers;
        delete ts;
    }

    uint8_t** encode(uint8_t *data,int32_t size,int64_t pts_us,int stream_type) {
        std::vector<MpegTsMuxer::TsBuffer> sb;
        memset(buffers,NULL,PACKET_NUM);
        ts->encode(data,size,pts_us,static_cast<MpegTsMuxer::TsStream>(stream_type),sb);
        const auto tmp_buffer_size = buffer_offset%PACKET_SIZE;
        if(tmp_buffer_size != 0){
            memcpy(buffer,buffer-(buffer_offset-tmp_buffer_size),tmp_buffer_size);
        }

        buffer_offset = tmp_buffer_size;
        for(int i = 0;i < sb.size(); i++){
            memcpy(buffer+buffer_offset,sb[i].data(),188);
            buffer_offset+=188;
            if(buffer_offset % PACKET_SIZE == 0){
                buffers[buffer_offset / PACKET_SIZE - 1] = &buffer[buffer_offset-PACKET_SIZE];
            }

        }

        return buffers;
    }

private:
    MpegTsMuxer::TsMuxer *ts;
    uint8_t **buffers;
    uint8_t *buffer;
    int buffer_offset;
};

Libmpegts::Libmpegts()
{
    impl = new LibmpegtsImpl();
}

Libmpegts::~Libmpegts()
{
    delete impl;
}

uint8_t **Libmpegts::encode(uint8_t *data, int32_t size, int64_t pts_us, int stream_type)
{
    return impl->encode(data,size,pts_us,stream_type);
}

