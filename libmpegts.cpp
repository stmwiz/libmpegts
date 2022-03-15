#include <vector>
#include <memory.h>

#include "libmpegts.hpp"
#include "src/muxer/ts_muxer.hpp"

class LibmpegtsImpl {
    static const int PACKET_NUM = 1024 * 8;
public:
    explicit LibmpegtsImpl(int ts_packet_size):ts_packet_size(ts_packet_size){
        ts = new MpegTsMuxer::TsMuxer();
        buffers = new uint8_t*[PACKET_NUM];
        buffer = new uint8_t[ts_packet_size * PACKET_NUM];
        buffer_offset = 0;
    }

    ~LibmpegtsImpl(){
        delete [] buffer;
        delete [] buffers;
        delete ts;
    }

    const int tsPacketSize() const {
        return this->ts_packet_size;
    }

    uint8_t** encode(uint8_t *data,int32_t size,int64_t pts_us,int stream_type) {
        std::vector<MpegTsMuxer::TsBuffer> sb;
        memset(buffers,NULL,PACKET_NUM);
        ts->encode(data,size,pts_us,static_cast<MpegTsMuxer::TsStream>(stream_type),sb);
        const auto tmp_buffer_size = buffer_offset%ts_packet_size;
        memcpy(buffer,buffer+(buffer_offset-tmp_buffer_size),tmp_buffer_size);
        buffer_offset = tmp_buffer_size;
        for(int i = 0;i < sb.size(); i++){
            memcpy(buffer+buffer_offset,sb[i].data(),188);
            buffer_offset+=188;
            if(buffer_offset % ts_packet_size == 0){
                buffers[buffer_offset / ts_packet_size - 1] = &buffer[buffer_offset-ts_packet_size];
            }

        }

        return buffers;
    }

private:
    MpegTsMuxer::TsMuxer *ts;
    uint8_t **buffers;
    uint8_t *buffer;
    int buffer_offset;
    int ts_packet_size;
};

Libmpegts::Libmpegts(int ts_packet_size)
{
    impl = new LibmpegtsImpl(ts_packet_size);
}

Libmpegts::~Libmpegts()
{
    delete impl;
}

const int Libmpegts::tsPacketSize() const{
    return impl->tsPacketSize();
}

uint8_t **Libmpegts::encode(uint8_t *data, int32_t size, int64_t pts_us, int stream_type)
{
    return impl->encode(data,size,pts_us,stream_type);
}

