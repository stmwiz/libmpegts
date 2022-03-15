#include <cstdio>
#include <fstream>
#include <vector>
#include <chrono>
#include <array>

#include "libmpegts.hpp"

int main() {
    printf("hello: %s %s %s\n",IN_AUDIO_RES_PATH,IN_VIDEO_RES_PATH,OUT_TS_RES_PATH);

    auto ts = Libmpegts();
    auto audio = ::fopen(IN_AUDIO_RES_PATH,"rb");
    auto video = ::fopen(IN_VIDEO_RES_PATH,"rb");
    auto out = ::fopen(OUT_TS_RES_PATH,"wb");
    if(audio == nullptr || video == nullptr || out == nullptr){
        return -1;
    }

    bool should_video = true;
    int audio_ret = 1,video_ret = 1,should_ret = 1;
    int stream_type = 0;
    int count = 0;
    while(audio_ret > 0 || video_ret > 0){
        std::array<uint8_t,1024> a{0xff};
        if(should_video){
            video_ret = ::fread(a.data(),1,a.size(),video);
            should_ret = video_ret;
            stream_type = Libmpegts::TS_H264;
            should_video = !should_video;
        }else {
            audio_ret = ::fread(a.data(),1,a.size(),audio);
            should_ret = audio_ret;
            stream_type = Libmpegts::TS_AAC;
            should_video = !should_video;
        }

        if(should_ret <=0){
            continue;
        }

        auto bf = ts.encode(a.data(),should_ret,30'000*count++,stream_type);
        while((*bf) != NULL){
            const auto ret = ::fwrite(*bf,1,ts.tsPacketSize(),out);
            printf("write bytes : %d\n",ret);
            ++bf;
        }

    }

    for(const auto &f:{audio,video,out}){
        fclose(f);
    }

    printf("mux over!!!\n");



    return 0;
}
