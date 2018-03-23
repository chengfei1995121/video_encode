#include "color_space.h"
#include <iostream>
#include <string.h>
#include <QDebug>
#include <math.h>
using namespace std;
ColorSpace::ColorSpace()
{
    table_init();
}
void ColorSpace::table_init()
{
    for(int32_t i=0;i < 256;i++)
    {
        table_u_to_g[i] =(100 * (i - 128)) >> 8;
        table_u_to_b[i] =(516 * (i - 128) + 128) >> 8;
        table_v_to_r[i] =(409 * (i - 128) + 128) >> 8;
        table_v_to_g[i] =(208 * (i - 128)) >> 8;
        table_y[i] = (298 * (i - 16)) >> 8;


        table_r_to_y[i] = 0.257 * i;
        table_g_to_y[i] = 0.504 * i;
        table_b_to_y[i] = 0.098 * i;
        table_r_to_u[i] = -0.148 * i;
        table_g_to_u[i] = 0.291 * i;
        table_b_to_u[i] =  0.439 * i;
        table_r_to_v[i] = 0.439 * i;
        table_g_to_v[i] = 0.368 * i;
        table_b_to_v[i] = 0.071 * i;
     }
}
int32_t ColorSpace::i420_to_rgb24_quick(const uint8_t *i420, uint8_t *rgb, int32_t width, int32_t height)
{
    const uint8_t *y_planer = i420;
    const uint8_t *u_planer = i420 + width * height;
    const uint8_t *v_planer = u_planer + width * height/4;
    float r,g,b;
    RGB *img_rgb=reinterpret_cast<RGB*>(rgb);
    int32_t y_stride  = width;
    int32_t uv_stride = width / 2;

    for(int32_t y_index = 0 ; y_index < height ; y_index++)
    {
        int32_t uv_y = y_index / 2;
        int32_t y_line = y_stride * y_index;
        for(int32_t x_index = 0; x_index < width ; x_index++)
        {
            int32_t uv_x = x_index / 2;
            uint8_t y = *(y_planer + (y_stride * y_index + x_index));
            uint8_t u = *(u_planer + (uv_stride * uv_y + uv_x));
            uint8_t v = *(v_planer + (uv_stride * uv_y + uv_x));
            r=table_y[y] + table_v_to_r[v];
            if(r<0)
                r=0;
            g = table_y[y] - table_u_to_g[u] - table_v_to_g[v];
            if(g<0)
                g=0;
            b = table_y[y] + table_u_to_b[u];
            if(b<0)
                b=0;
            img_rgb->r = r;
            img_rgb->g = g;
            img_rgb->b = b;
            img_rgb++;
        }
    }
    return 0;


}
int32_t ColorSpace::i420_to_rgb24(const uint8_t *i420, uint8_t *rgb, int32_t width, int32_t height)
{
    float r,g,b;    
    RGB *img_rgb=reinterpret_cast<RGB*>(rgb);

    const uint8_t* y_planer = i420;
    const uint8_t* u_planer = y_planer + width * height;
    const uint8_t* v_planer = u_planer + width * height / 4;

    int32_t y_stride  = width;
    int32_t uv_stride = width / 2;

    for(int32_t y_index = 0 ; y_index < height ; y_index++)
    {
        int32_t uv_y = y_index / 2;
        for(int32_t x_index = 0; x_index < width ; x_index++)
        {

            int32_t uv_x = x_index / 2;
            uint8_t y = *(y_planer + (y_stride * y_index + x_index));
            uint8_t u = *(u_planer + (uv_stride * uv_y + uv_x));
            uint8_t v = *(v_planer + (uv_stride * uv_y + uv_x));
            r = 1.164 * (y - 16) + 1.596 * (v - 128);
            if(r<0)
                r=0;
            g = 1.164 * (y - 16) - 0.391 * (u - 128) - 0.813 * (v -128);
            if(g<0)
                g=0;
            b = 1.164 * (y - 16) + 2.018 * (u  - 128);
            if(b<0)
                b=0;
            img_rgb->r = r;
            img_rgb->g = g;
            img_rgb->b = b;
            img_rgb++;
        }
    }
    return 0;
}

int32_t ColorSpace::rgb24_to_i420(uint8_t *rgb, uint8_t *i420, int32_t width, int32_t height)
{
    RGB *img_rgb=reinterpret_cast<RGB*>(rgb);
    float yy,uu,vv;
    int pos=0,upos=0,vpos=0;
    for(int32_t y=0;y<height;y++)
    {
        for(int32_t x=0;x<width;x++)
        {
            yy=table_r_to_y[img_rgb->r] + table_g_to_y[img_rgb->g]  + table_b_to_y[img_rgb->b] + 16;
            i420[pos]=(uint8_t)floor(yy);
            uu=table_r_to_u[img_rgb->r] - table_g_to_u[img_rgb->g] + table_b_to_u[img_rgb->b] + 128;
            vv=table_r_to_v[img_rgb->r] - table_g_to_v[img_rgb->g] - table_b_to_v[img_rgb->b] + 128;
            if(y%2==0&&x%2==0)
            {
                i420[upos+height*width]=(uint8_t)floor(uu);
                upos++;
                i420[width*height+width*height/4+vpos]=(uint8_t)vv;
                vpos++;
            }
            pos++;
            img_rgb++;
        }
    }
    return 0;
}

void ColorSpace::rgba_compose(int32_t width,int32_t height,int32_t funny_width,int32_t funny_height,int32_t x,int32_t y,uint8_t *target_rgba,uint8_t *bg_rgba, uint8_t *funny_image)
{
    x = x - funny_width / 2;
    y = y - funny_height / 2;
    x=x >= width - funny_width ? width - funny_width : x;
    x=x < 0   ? 0   : x;
    y=y >= height - funny_height ? height - funny_height : y;
    y=y < 0   ? 0   : y;
    float r,g,b;

    int32_t x_rang = x + funny_width;
    int32_t y_rang = y + funny_height;
    for(int32_t yy = 0;yy<height; yy++)
    {
        for(int32_t xx = 0;xx < width; xx++)
        {
        if(yy>=y && yy < y_rang && xx >= x && xx < x_rang)
        {
            float alpha_funny=*(funny_image + 3)*1.0 / 255;
            float alpha_bg = (255 - (*(funny_image + 3))) * 1.0 /255;
            r = (*(funny_image)) * alpha_funny + alpha_bg * (*bg_rgba);
            g = (*(funny_image + 1)) * alpha_funny + alpha_bg * (*(bg_rgba+1));
            b = (*(funny_image + 2)) * alpha_funny + alpha_bg * (*(bg_rgba+2));
            *(target_rgba) = r;
            *(target_rgba+1) = g;
            *(target_rgba+2) = b;
            bg_rgba += 4;
            target_rgba += 3;
            funny_image += 4;
        }
        else
        {
            *(target_rgba) = *(bg_rgba);
            *(target_rgba + 1) = *(bg_rgba + 1);
            *(target_rgba + 2) = *(bg_rgba + 2);
            target_rgba += 3;
            bg_rgba += 4;
        }
        }
    }

}
