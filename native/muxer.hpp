//
// Copyright (c) 2019-2022 gaofeng akanchi
//

#ifndef TS_TSMUXER_H_
#define TS_TSMUXER_H_
#include "stdint.h"
#include <vector>
#include <map>

#include "TsBuffer.hpp"
#include "TsPacket.h"
#include "TsPid.h"
using namespace std;

/**
static const int32_t DEFAULT_PCR_PID = 4097;
static const int32_t DEFAULT_PMT_PID = 256;

static const uint8_t SEQUENCE_END_CODE = 0xb7;
static const uint8_t ISO_11172_END_CODE = 0xb9;
static const uint8_t PACK_START_CODE = 0xba;
static const uint8_t SYSTEM_HEADER_START_CODE = 0xbb;
static const uint8_t PES_PROGRAM_STREAM_MAP = 0xbc;
static const uint8_t PES_PRIVATE_DATA1 = 0xbd;
static const uint8_t PADDING_STREAM = 0xbe;
static const uint8_t PES_PRIVATE_DATA2 = 0xbf;
static const uint8_t PROGRAM_STREAM_DIRECTORY = 0xff;

static const uint8_t PES_AUDIO_ID = 0xc0;
static const uint8_t PES_VIDEO_ID = 0xe1;
static const uint8_t PES_VC1_ID = 0xfd;

static const uint8_t DVB_SUBT_DESCID = 0x59;

static const uint8_t STREAM_TYPE_VIDEO_MPEG1 = 0x01;
static const uint8_t STREAM_TYPE_VIDEO_MPEG2 = 0x02;
static const uint8_t STREAM_TYPE_PRIVATE_SECTION = 0x05;
static const uint8_t STREAM_TYPE_PRIVATE_DATA = 0x06;
static const uint8_t STREAM_TYPE_VIDEO_MPEG4 = 0x10;
static const uint8_t STREAM_TYPE_VIDEO_H264 = 0x1b;
static const uint8_t STREAM_TYPE_VIDEO_MVC = 0x20;
static const uint8_t STREAM_TYPE_VIDEO_H265 = 0x24;
static const uint8_t STREAM_TYPE_VIDEO_VC1 = 0xea;

static const uint8_t STREAM_TYPE_AUDIO_MPEG1 = 0x03;
static const uint8_t STREAM_TYPE_AUDIO_MPEG2 = 0x04;
static const uint8_t STREAM_TYPE_AUDIO_AAC = 0x0f;
static const uint8_t STREAM_TYPE_AUDIO_AAC_RAW = 0x11;
static const uint8_t STREAM_TYPE_AUDIO_DTS = 0x82;  // 0x8a

static const uint8_t STREAM_TYPE_AUDIO_LPCM = 0x80;
static const uint8_t STREAM_TYPE_AUDIO_AC3 = 0x81;
static const uint8_t STREAM_TYPE_AUDIO_EAC3 = 0x84;
static const uint8_t STREAM_TYPE_AUDIO_EAC3_ATSC = 0x87;
static const uint8_t STREAM_TYPE_AUDIO_EAC3_TRUE_HD = 0x83;
static const uint8_t STREAM_TYPE_AUDIO_DTS_HD = 0x85;
static const uint8_t STREAM_TYPE_AUDIO_DTS_HD_MASTER_AUDIO = 0x86;

static const uint8_t STREAM_TYPE_AUDIO_EAC3_SECONDARY = 0xA1;
static const uint8_t STREAM_TYPE_AUDIO_DTS_HD_SECONDARY = 0xA2;

static const uint8_t STREAM_TYPE_AUDIO_VC9 = 0x88;
static const uint8_t STREAM_TYPE_AUDIO_OPUS = 0x89;
static const uint8_t STREAM_TYPE_SUB_PGS = 0x90;

static const uint8_t STREAM_TYPE_SUBTITLE_DVB = 0x00;
**/
#define pat_interval  50
enum TsStream{
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
class TsMuxer {
public:
	TsMuxer();
	virtual ~TsMuxer();
    void create_pat(TsBuffer *sb, uint16_t pmt_pid, uint8_t cc);
    void create_pmt(TsBuffer *sb,uint8_t cc);
    void create_ts(TsPes *frame,vector<TsBuffer>  *sb);
    void create_pes(TsPes *frame,uint8_t *p,int32_t plen,int32_t frametype,int64_t timestamp,TsStream streamType);
    void create_pcr(TsBuffer *sb);
    void create_null(TsBuffer *sb);
    void encode(uint8_t* p,int32_t plen,int32_t frametype,int64_t timestamp ,TsStream streamType,vector<TsBuffer> *sb);
    void encodeWithPmt(uint8_t* p,int32_t plen,int32_t frametype,int64_t timestamp ,TsStream streamType,vector<TsBuffer> *sb);
    //void encodePmt(vector<TsBuffer> *sb);
    void encodePmtWithoutData(vector<TsBuffer> *sb);
    std::map<uint8_t, int> m_stream_pid_map;
private:
    uint8_t get_cc(uint32_t with_pid);
    bool should_create_pat();
    int32_t m_pmt_pid;

      int32_t current_index;
private:
    std::map<uint32_t, uint8_t> _pid_cc_map;
};

#endif /* TS_TSMUXER_H_ */
