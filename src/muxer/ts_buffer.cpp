#include <cassert>
#include <memory.h>
#include <cstdint>

#include "ts_buffer.hpp"

namespace MpegTsMuxer {

void TsBuffer::write_1byte(char val)
{
    data_[cur_pos_++]=val;
}

void TsBuffer::write_2bytes(int16_t val)
{
    char *p = (char *)&val;

    for (int32_t i = 1; i >= 0; --i) {
        data_[cur_pos_++] = p[i];
    }
}

void TsBuffer::write_3bytes(int32_t val)
{
    char *p = (char *)&val;

    for (int32_t i = 2; i >= 0; --i) {
        data_[cur_pos_++]=p[i];
    }
}

void TsBuffer::write_4bytes(int32_t val)
{
    char *p = (char *)&val;

    for (int32_t i = 3; i >= 0; --i) {
        data_[cur_pos_++]=p[i];
    }
}

void TsBuffer::write_8bytes(int64_t val)
{
    char *p = (char *)&val;

    for (int32_t i = 7; i >= 0; --i) {
        data_[cur_pos_++]=p[i];
    }
}
void TsBuffer::write_bytes(uint8_t* bytes,int32_t size){
    memcpy(data_+ cur_pos_,bytes,size);
    cur_pos_+=size;
}

void TsBuffer::append( uint8_t* bytes, int32_t size)
{
    if (!bytes || size <= 0)
        return;
    memcpy(data_+cur_pos_,bytes,size);
    cur_pos_+=size;
}

char TsBuffer::read_1byte()
{
    assert(require(1));

    char val = data_[pos_];
    pos_++;

    return val;
}

int16_t TsBuffer::read_2bytes()
{
    assert(require(2));

    int16_t val = 0;
    char *p = (char *)&val;

    for (int32_t i = 1; i >= 0; --i) {
        p[i] = data_[pos_];
        pos_++;
    }

    return val;
}

int32_t TsBuffer::read_3bytes()
{
    assert(require(3));

    int32_t val = 0;
    char *p = (char *)&val;

    for (int32_t i = 2; i >= 0; --i) {
        p[i] =  data_[pos_];//data_.at(0 + pos_);
        pos_++;
    }

    return val;
}

int32_t TsBuffer::read_4bytes()
{
    assert(require(4));

    int32_t val = 0;
    char *p = (char *)&val;

    for (int32_t i = 3; i >= 0; --i) {
        p[i] =  data_[pos_];
        pos_++;
    }

    return val;
}

int64_t TsBuffer::read_8bytes()
{
    assert(require(8));

    int64_t val = 0;
    char *p = (char *)&val;

    for (int32_t i = 7; i >= 0; --i) {
        p[i] =  data_[pos_];
        pos_++;
    }

    return val;
}

void TsBuffer::read_bytes(uint8_t *p,int32_t len){
    memcpy(p,data_+pos_,len);
    pos_ += len;
}

std::string TsBuffer::read_string(int32_t len)
{
    assert(require(len));

    std::string val((char*)data_ + pos_, len);
    pos_ += len;

    return val;
}

void TsBuffer::skip(int32_t size)
{
    pos_ += size;
}

bool TsBuffer::require(int32_t required_size)
{
    assert(required_size >= 0);

    return required_size <= cur_pos_- pos_;
}

bool TsBuffer::empty() const
{
    return pos_ >= cur_pos_;
}

int32_t TsBuffer::size() const
{
    return cur_pos_;
}

int32_t TsBuffer::pos() const
{
    return pos_;
}

uint8_t *TsBuffer::data()
{
    return (size() == 0) ? nullptr : data_;
}

void TsBuffer::clear()
{
    pos_ = 0;
    cur_pos_=0;

}

void TsBuffer::set_data(int32_t pos, const uint8_t *data, int32_t len)
{
    if (!data)
        return;

    if (pos + len > size()) {
        return;
    }

    for (int32_t i = 0; i < len; i++) {
        data_[pos + i] = data[i];
    }
}

std::string TsBuffer::to_string()
{
    return std::string(data_, data_+cur_pos_);
}

}
