#ifndef IMAGE_GENERATE_H
#define IMAGE_GENERATE_H
#include <stdint.h>
#include <stdio.h>
#include <iostream>
struct RGB{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct RGBA{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; //alpha channel
};
class Image
{
public:
    Image(int32_t width, int32_t height);
    virtual void create();
    virtual uint8_t* get_data();
    virtual ~Image();
protected:
    int32_t width_;
    int32_t height_;
};

class ImageRgb:public Image
{
public:
    ImageRgb(int32_t,int32_t);
    void create();
    uint8_t* get_data();
    ~ImageRgb();
private:
    uint8_t *rgb_data_ = nullptr;
};

class ImageRgba:public Image
{
public:
    ImageRgba(int32_t width,int32_t height);
    void create();
    uint8_t* get_data();
    ~ImageRgba();
private:
    uint8_t *rgba_data_ = nullptr;
};

class FactoryRgb
{
public:
    Image* create_image(int32_t width,int32_t height);
};

class FactoryRgba
{
public:
    Image* create_image(int32_t width,int32_t height);
};

#endif // IMAGE_GENERATE_H
