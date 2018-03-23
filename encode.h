#ifndef X264_ENCODE_H
#define X264_ENCODE_H
#include <iostream>
#include <stdio.h>
#include "x264.h"
#include <stdint.h>
#include <string.h>
#include <observer.h>


using namespace std;

class Encode{
public:
    Encode();
    int video_encode(uint8_t *i_420, int timestamp);
    void video_encode_muxer_open(int32_t width, int32_t height);
    void set_observer(Observer *observer);
    ~Encode();
    void flush_encode();


private:
    x264_t           *pHandle_       = nullptr;
    x264_param_t     *pParam_        = nullptr;
    x264_picture_t   *p_in_          = nullptr;
    x264_picture_t   *p_out_         = nullptr;
    x264_nal_t       *pNals_         = nullptr;
    int              csp_            = X264_CSP_I420;
    int              y_size_         = 0;
    int              i_nals_         = 0;
    Observer         *observer_      = nullptr;
};

#endif // X264_ENCODE_H
