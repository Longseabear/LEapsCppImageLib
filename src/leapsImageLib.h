
#ifndef __LEAPS_IMAGE_LIB__
#define __LEAPS_IMAGE_LIB__

#include "./lodepng.h"

namespace LeapsImageLib{
    using uchar = unsigned char;
    using uint = unsigned int;
    class Image
    {
    public:
        Image();
        Image(uint, uint);
        Image(const char*);
        uint width, height;
        uchar* ptr(uint);
        uchar* ptr(uint, uint);
        void save(const char*);

        //Todo: private
        std::vector<uchar> raw; 
    private:
    };
}

#endif