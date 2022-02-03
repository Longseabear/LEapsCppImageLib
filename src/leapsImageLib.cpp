
#include "leapsImageLib.h"
#include "converter.h"
#include <iostream>
using namespace std;
using namespace LeapsImageLib;

template <>
LeapsImageLib::Image<LeapsImageLib::uint8_t>::Image(const char* filename){
    unsigned error = lodepng::decode(raw, width, height, filename);
    setChannel(4);
    setColorFormat(CF_RGBA_8U);

    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        throw exception();
    }
}
template <>
LeapsImageLib::Image<_Float64>::Image(const char* filename){
    auto temp_image = Image<uint8_t>(filename);

    unsigned w = temp_image.getWidth();
    unsigned h = temp_image.getHeight();
    unsigned c = temp_image.getChannel();
    raw.resize((w*h*c));

    setWidth(temp_image.getWidth());
    setHeight(temp_image.getHeight());
    setChannel(temp_image.getChannel());
    setColorFormat(CF_RGBA_64F);
    
    uint8_t* ptr = temp_image.ptr(0);
    for(int i=0; i<width*height; i++) raw[i] = (_Float64)ptr[i] / 255.;
}
template <>
LeapsImageLib::Image<_Float32>::Image(const char* filename){
auto temp_image = Image<uint8_t>(filename);

    unsigned w = temp_image.getWidth();
    unsigned h = temp_image.getHeight();
    unsigned c = temp_image.getChannel();
    raw.resize((w*h*c));
 
    setWidth(temp_image.getWidth());
    setHeight(temp_image.getHeight());
    setChannel(temp_image.getChannel());
    setColorFormat(CF_RGBA_32F);
    
    uint8_t* ptr = temp_image.ptr(0);
    for(int i=0; i<width*height; i++) raw[i] = (_Float32)ptr[i] / 255.;
}

//#define rgb2yuv(R,G,B) ((((((66*R+129*G+25*B+128)>>8)+16)<<8)|(((112*R-94*G-18*B+128)>>8)+128))<<8|(((-38*R-74*G+112*B+128)>>8)+128))

/*
    args: img(CF_RGBA_8U)
    return: img(CF_GRAY_8U)
*/
Image<uint8_t> im_RGBA8UToGRAY8(Image<uint8_t>& img){
    if(img.getColorFormat() != CF_RGBA_8U){
        std::cout << "RGBA_8U_to_GRAY_8U function only support CF_RGBA_8U color format and but: " \
        << colorFormatToString[img.getColorFormat()] << endl;
        throw exception();
    }

    Image<uint8_t> out = Image<uint8_t>(img.getWidth(), img.getHeight(), img.getChannel(), CF_GRAY_8U);
    auto dst = out.ptr(0);
    uint32_t* src = (uint32_t*)img.ptr(0);    
    int bytelen = img.getWidth() * img.getHeight() * img.getChannel();

    for(int i=0; i<bytelen; ++i){
        RGBA8UToGRAY8(src[i], dst[i]);
    }

    return out;
}

