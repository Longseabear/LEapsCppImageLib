
#include "leapsImageLib.h"
#include <iostream>
using namespace std;
using namespace LeapsImageLib;

// Image[Y][X] []
LeapsImageLib::Image::Image(): width(0), height(0){}
LeapsImageLib::Image::Image(uint w, uint h): width(w), height(h){}
LeapsImageLib::Image::Image(const char* filename){
    unsigned error = lodepng::decode(raw, width, height, filename);
    if(error){
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        throw exception();
    }
}
uchar* Image::ptr(uint row){
    return &raw[0] + ((width * row) << 2);
}
uchar* Image::ptr(uint row, uint col){
    return &raw[0] + (width * row * 4) + col * 4;
}
void Image::save(const char* filename){
    unsigned error = lodepng::encode(filename, raw, width, height);
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

using namespace LeapsImageLib;
int main(int argc, char *argv[])
{
    const char *filename = argc > 1 ? argv[1] : "../Lenna.png";
    printf("hello world");
    Image img = Image(filename);
    for(int i=0;i<img.width;i++){
        auto pixel = img.ptr(0, i);
        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 0;
    }
    img.save("../output.png");
}
