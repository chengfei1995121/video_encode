#ifndef X264_TO_MP4_H
#define X264_TO_MP4_H
#define STREAM_FREAM_RATE 25
#include <iostream>
#include <stdio.h>
#include <string.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

class MyMuxer{
public:
    MyMuxer() = default;
    MyMuxer(int32_t,int32_t,const char*);
    AVStream* add_stream(AVFormatContext *ofmt_ctx_, AVCodec **codec_, enum AVCodecID codec_id,uint8_t *data, int data_size);
    void write_h264(uint8_t *data, int lenght, bool keyframe, int32_t timestamp_ms);
    void tran_open(int32_t width, int32_t height, char *filename, uint8_t *data, int data_size);
    void closemp4();

private:
    int32_t          width_        = 0;
    int32_t          height_       = 0;
    int              vi_           = 0;
    const char       *filename_    = nullptr;
    AVOutputFormat   *ofmt_        = nullptr;
    AVFormatContext  *ofmt_ctx_    = nullptr;
    AVStream         *out_stream_  = nullptr;
    AVCodec          *codec_       = nullptr;
};
#endif // X264_TO_MP4_H
