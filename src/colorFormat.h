#ifndef __LEAPS_IMAGE_LIB_COLOR_FORMAT__
#define __LEAPS_IMAGE_LIB_COLOR_FORMAT__

namespace LeapsImageLib{ /* start LeapsImageLib namepsace*/
    using namespace std;
    #define COLOR_FORMAT_TO_STRING_MAX_SIZE 10
    
    enum ColorFormat{
        CF_GRAY_8U,     // GRAY scale(luminance), 8 bit unsigned format
        CF_RGBA_8U,     // RGBA order, 8 bit unsigned format
        CF_RGBA_32F,    // RGBA order, 32 single precision(float)
        CF_RGBA_64F,    // RGBA order, 64 double precision(double)
    };
    extern const char* const colorFormatToString[COLOR_FORMAT_TO_STRING_MAX_SIZE];
}

#endif