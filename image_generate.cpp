#include "image_generate.h"
#include <iostream>
using namespace std;

Image::Image(int32_t width,int32_t height):width_(width),height_(height)
{

}

 void Image::create()
 {

 }
 Image::~Image()
 {

 }
 uint8_t* Image::get_data()
 {

 }
ImageRgb::ImageRgb(int32_t width,int32_t height):Image(width,height)
{

}


ImageRgb::~ImageRgb()
{
    delete []rgb_data_;
}


void ImageRgb::create()
{
    rgb_data_ = new uint8_t[width_ * height_ *3];
    RGB colors[] = {{255,0,40},
                 {143,255,0},
                 {0,150,255}};
    RGB* rgb  = reinterpret_cast<RGB*>(rgb_data_);
    for(int32_t y = 0; y < height_; y++){
        for(int32_t x = 0; x < width_; x++){
            int32_t color_index = (y / 32) % 3;
            *rgb = colors[color_index];
            rgb++;
        }
    }
}

uint8_t* ImageRgb::get_data()
{
    if(rgb_data_ != nullptr)
        return rgb_data_;
    else
    {
        printf("%s\n","data is NULL");
        return nullptr;
    }
}

ImageRgba::ImageRgba(int32_t width,int32_t height):Image(width,height)
{

}


ImageRgba::~ImageRgba()
{
    delete []rgba_data_;
}

void ImageRgba::create()
{
    rgba_data_ = new uint8_t[width_ * height_ * 4];
    RGBA colors[] = {{255,0,0,255},
                 {0,255,0,255},
                 {0,0,255,255}};
    RGBA* rgba  = reinterpret_cast<RGBA*>(rgba_data_);
    for(int32_t y = 0; y < height_; y++){
        for(int32_t x = 0; x < width_; x++){
                   int32_t color_index = (y / 32) % 3;
                    *rgba = colors[color_index];
                    rgba++;
           }
    }
}

uint8_t* ImageRgba::get_data()
{
    if(rgba_data_ != nullptr)
        return rgba_data_;
    else
    {
        printf("%s\n","data is NULL");
        return nullptr;
    }
}

Image* FactoryRgb::create_image(int32_t width,int32_t height)
{
    return new ImageRgb(width,height);
}

Image* FactoryRgba::create_image(int32_t width,int32_t height)
{
    return new ImageRgba(width,height);
}
