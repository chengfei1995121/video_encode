#include "encode.h"


Encode::Encode():pParam_(new x264_param_t),p_out_(new x264_picture_t),p_in_(new x264_picture_t)
{

}

Encode::~Encode()
{

    delete p_in_;
    delete p_out_;
    delete pParam_;
    if(pHandle_ == nullptr)
    {
        cout<<"this is null"<<endl;
    }

}
void Encode::set_observer(Observer *observer)
{
    observer_ = observer;
}
void Encode::video_encode_muxer_open(int32_t width,int32_t height)
{
    y_size_ = width * height;
    int ret = 0;
    x264_param_default(pParam_);
    x264_param_default_preset(pParam_,"veryfast","fastdecode");
    x264_param_apply_profile(pParam_,x264_profile_names[0]);

    pParam_->i_width  = width;
    pParam_->i_height = height;
    pParam_->i_csp    = csp_;
    pParam_->i_fps_den = 1;
    pParam_->i_fps_num = 1000;

    pHandle_ = x264_encoder_open(pParam_);

    x264_picture_init(p_out_);
    x264_picture_alloc(p_in_,csp_,width,height);
    ret = x264_encoder_headers(pHandle_,&pNals_,&i_nals_);
    ret = ret - pNals_[2].i_payload;


    //open muxer
    observer_->on_sps_pps(pNals_->p_payload,ret);
}
int Encode::video_encode(uint8_t *i_420,int timestamp)
{
        int ret = 0;

        memcpy(p_in_->img.plane[0],i_420,y_size_);
        i_420 += y_size_;
        memcpy(p_in_->img.plane[1],i_420,y_size_ / 4);
        i_420 += y_size_ / 4;
        memcpy(p_in_->img.plane[2],i_420,y_size_ / 4);
        p_in_->i_pts = timestamp;
        p_in_->i_dts = timestamp;
        ret = x264_encoder_encode(pHandle_,&pNals_,&i_nals_,p_in_,p_out_);
        if(ret < 0)
        {
            cout<<"encode failed"<<endl;
            return -1;
        }
        else if(ret > 0){
            observer_->on_encode_frame(pNals_->p_payload,ret,IS_X264_TYPE_I(p_out_->i_type),p_out_->i_pts);
        }
}
void Encode::flush_encode()
{
    int ret =0;

    while(1)
    {
        ret = x264_encoder_encode(pHandle_,&pNals_,&i_nals_,NULL,p_out_);
        if(ret == 0)
        {
            break;
        }
        for(int j=0;j < i_nals_;j++)
        {
            observer_->on_encode_frame(pNals_[j].p_payload,pNals_[j].i_payload,IS_X264_TYPE_I(p_out_->i_type),p_out_->i_pts);
        }
    }
    x264_picture_clean(p_in_);
    x264_encoder_close(pHandle_);
}






