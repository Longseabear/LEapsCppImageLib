#include <stdio.h>
#include "leapsImageLib.h"
#include <cassert>
using namespace LeapsImageLib;

bool uTest_copy_and_swap(){
    Image<uint8_t> A(3,3);
    Image<uint8_t> B(A);

    // copy constructor check
    auto ptr = A.ptr(0);
    auto ptr2 = B.ptr(0);

    assert(B.getWidth() != 7);
    assert(ptr!=ptr2);

    // move constructor check
    Image<uint8_t> C(std::move(A));
    auto ptr3 = C.ptr(0);
    assert(ptr==ptr3);
    assert(ptr2!=ptr3);

    // copy assignment check
    B = C;
    assert(B.ptr(0) != ptr3);
    assert(B.ptr(0) != C.ptr(0));


    printf("clear uTest_copy_and_swap\n");
    return true;
}
bool uTest_rgb2gray(){
    auto img = Image<uint8_t>("img/Lenna.png");
    auto pixel = img.ptr(0, 0);
    for(int i=0;i<20;i++){
        printf("%lf ", pixel[i]);
    }
}
bool uTest_png_load_save(){
    auto img = Image<uint8_t>("img/Lenna.png");

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

#if __BYTE_ORDER__ == __LITTLE_ENDIAN
    printf("hello little endian\n");
#else
    printf("hello big endian\n");
#endif
    printf("test start\n");
//    uTest_png_load_save();
    uTest_copy_and_swap();
    return 0;
}