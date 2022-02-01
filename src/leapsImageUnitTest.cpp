#include <stdio.h>
#include "leapsImageLib.h"

using namespace LeapsImageLib;

bool uTest_rgb2gray(){
    auto img = Image<uchar>("img/Lenna.png");

    auto pixel = img.ptr(0, 0);
    for(int i=0;i<20;i++){
        printf("%lf ", pixel[i]);
    }
}
bool uTest_png_load_save(){
    auto img = Image<uchar>("img/Lenna.png");

    auto pixel = img.ptr(0, 0);
    printf("width: %d, height: %d, channel: %d\n", img.getWidth(), img.getHeight(), img.getChannel());
    for(uint i=0;i<img.getWidth() * img.getChannel();i++){
        pixel[i] = 0;
    }
    img.save("out.png");
    static_assert(true);
    return true;
}
int main(){
    printf("test start");
    uTest_png_load_save();
    return 1;
}