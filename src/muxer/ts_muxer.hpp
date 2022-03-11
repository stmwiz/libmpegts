#pragma once

#include <vector>
#include <unordered_map>

#include "ts_buffer.hpp"
#include "ts_packet.hpp"
#include "ts_pid.hpp"

class TsMuxer {
    enum TsStream {
        TS_H264,
        TS_H265,
        TS_AAC,
        TS_OPUS,
        TS_PRIVATE
    };

    struct TsPes{
        uint8_t *data;
        int32_t len;
        int32_t pos;
        uint64_t pts;
        uint64_t dts;
        uint64_t pcr;
        uint8_t stream_type;
        uint8_t stream_id;
        uint16_t pid;
    };

    static const int PAT_INTERVAL = 50;
    static const uint16_t MPEGTS_NULL_PACKET_PID = 0x1FFF;
    static const uint16_t MPEGTS_PAT_PID = 0x00;
    static const uint16_t MPEGTS_PMT_PID = 0x100;
    static const uint16_t MPEGTS_PCR_PID = 0x110;
public:
    explicit TsMuxer();
    virtual ~TsMuxer();
    void create_pat(TsBuffer *sb, uint16_t pmt_pid, uint8_t cc);
    void create_pmt(TsBuffer *sb,uint8_t cc);
    void create_ts(TsPes *frame,std::vector<TsBuffer> &sb);
    void create_pes(TsPes *frame,uint8_t *p,int32_t plen,int32_t frametype,int64_t timestamp,TsStream streamType);
    void create_pcr(TsBuffer *sb);
    void create_null(TsBuffer *sb);
    void encode(uint8_t* p,int32_t plen,int32_t frametype,int64_t timestamp ,TsStream streamType,std::vector<TsBuffer> &sb);
    void encode_with_pmt(uint8_t* p,int32_t plen,int32_t frametype,int64_t timestamp ,TsStream streamType,std::vector<TsBuffer> &sb);
    void encode_pmt_without_data(std::vector<TsBuffer> &sb);
    std::unordered_map<uint8_t, int> m_stream_pid_map;
private:
    uint8_t get_cc(uint32_t with_pid);
    bool should_create_pat();
    int32_t m_pmt_pid;
    int32_t current_index;
private:
    std::unordered_map<uint32_t, uint8_t> pid_cc_map;
};

