#ifndef OBSERVER_H
#define OBSERVER_H
#include <stdint.h>


class Observer
{
public:
    Observer() = default;
    virtual void on_sps_pps(uint8_t *sps_pps,int32_t lenght) = 0;

    virtual void on_encode_frame(uint8_t *frame,int32_t frame_size,bool keyframe,int64_t pts) = 0;
};


#endif // OBSERVER_H
