#ifndef COLOR_SPACE_H
#define COLOR_SPACE_H
#include <stdint.h>
#include "image_generate.h"
class ColorSpace
{
public:
    ColorSpace();
    int32_t rgb24_to_i420(uint8_t* rgb,uint8_t *i420,int32_t width,int32_t height);
    int32_t i420_to_rgb24(const uint8_t* i420,uint8_t* rgb,int32_t width,int32_t height);
    int32_t i420_to_rgb24_quick(const uint8_t *i420, uint8_t *rgb, int32_t width, int32_t height);

    void table_init();

    void rgba_compose(int32_t width,int32_t height,int32_t funny_width,int32_t funny_height,int32_t x,int32_t y,uint8_t *target_rgba,uint8_t *bg_rgba, uint8_t *funny_image);

    void rgba_to_rgb(int32_t width,int32_t height,uint8_t *target_rgba,uint8_t *dst_rgb);
private:
    float table_y[256];
    float table_u_to_g[256];
    float table_u_to_b[256];
    float table_v_to_r[256];
    float table_v_to_g[256];
    float table_r_to_y[256];
    float table_g_to_y[256];
    float table_b_to_y[256];
    float table_r_to_u[256];
    float table_g_to_u[256];
    float table_b_to_u[256];
    float table_r_to_v[256];
    float table_g_to_v[256];
    float table_b_to_v[256];
};

#endif // COLOR_SPACE_H
