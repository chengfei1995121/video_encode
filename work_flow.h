#ifndef WORK_FLOW_H
#define WORK_FLOW_H
#include "observer.h"
#include "encode.h"
#include "x264_to_mp4.h"

class Workflow:public Observer{
public:
    Workflow();
    void on_sps_pps(uint8_t *,int32_t) override;
    void on_encode_frame(uint8_t *frame,int32_t frame_size,bool keyframe,int64_t pts) override;
    void create_viedo(char*,int32_t,int32_t);
    void encode_frame(uint8_t*,int32_t);
    void close();

private:

    MyMuxer muxer_;
    Encode  encode_;
    int32_t width_;
    int32_t height_;
    char*   filename_;
};


#endif // WORK_FLOW_H
