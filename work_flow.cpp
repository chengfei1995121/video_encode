#include "work_flow.h"

Workflow::Workflow()
{
    encode_.set_observer(this);
}

void Workflow::create_viedo(char *filename,int width,int height)
{
    width_ = width;
    height_ = height;
    filename_ = filename;
    encode_.video_encode_muxer_open(width,height);
}

void Workflow::encode_frame(uint8_t *frame,int32_t pts)
{
    encode_.video_encode(frame,pts);
}

void Workflow::on_sps_pps(uint8_t * data,int32_t size)
{
    muxer_.tran_open(width_,height_,filename_,data,size);
}

void Workflow::on_encode_frame(uint8_t *frame,int32_t frame_size,bool keyframe,int64_t pts)
{
    muxer_.write_h264(frame,frame_size,keyframe,pts);
}

void Workflow::close()
{
    encode_.flush_encode();
    muxer_.closemp4();
}
