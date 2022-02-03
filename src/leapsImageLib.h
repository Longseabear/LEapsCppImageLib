
#ifndef __LEAPS_IMAGE_LIB__
#define __LEAPS_IMAGE_LIB__

#include "./lodepng.h"
#include "colorFormat.h"
#include "converter.h"
#include <vector>
#include <iostream>

namespace LeapsImageLib{ /* start LeapsImageLib namepsace*/
    using namespace std;

    #define rgb2yuv(R,G,B) ((((((66*R+129*G+25*B+128)>>8)+16)<<8)|(((112*R-94*G-18*B+128)>>8)+128))<<8|(((-38*R-74*G+112*B+128)>>8)+128))

    template <class T>
    class Image
    {
    public:
        Image() = delete;
        Image(unsigned, unsigned);
        Image(unsigned, unsigned, unsigned);
        Image(unsigned, unsigned, unsigned, ColorFormat);
        Image(const char*);
        
        Image(const Image& other){
            this->width = other.width;
            this->height = other.height;
            this->channel = other.channel;
            this->colorFormat = other.colorFormat;
            this->raw = vector<T>(other.raw);
        }
        Image(Image&& other) noexcept: Image(0,0) {  // because of irreversible mutation
            swap(*this, other);
        };
        Image& operator=(Image other){
            swap(*this, other);
            return *this;
        } 
        Image& operator=(Image&& other) noexcept{
//            swap(*this, other);
        };  //

        void save(const char*);
        T* ptr(unsigned);
        T* ptr(unsigned, unsigned);
        
        // image property
        void setWidth(unsigned _w){
            width = _w;
        };
        void setHeight(unsigned _h){
            height = _h;
        }
        void setChannel(unsigned _c){
            channel = _c;
        }
        void setColorFormat(ColorFormat _cf){
            colorFormat = _cf;
        }
        unsigned getChannel(){
            return channel;
        }
        unsigned getWidth(){
            return width;
        }
        unsigned getHeight(){
            return height;
        }
        pair<unsigned, unsigned> getSize(){
            return {height, width}; 
        } // height, width
        ColorFormat getColorFormat(){
            return colorFormat;
        }
        
        friend void swap(Image& first, Image& second){
            using std::swap;

            swap(first.width, second.width);
            swap(first.height, second.height);
            swap(first.channel, second.channel);
            swap(first.colorFormat, second.colorFormat);
            swap(first.raw, second.raw);
        }
    private:
        std::vector<T> raw; //RGBA
        ColorFormat colorFormat;
        unsigned width, height, channel;
    };

    // template <class T>
    // LeapsImageLib::Image<T>::Image(): width(0), height(0), channel(0) {}

    template <class T>
    LeapsImageLib::Image<T>::Image(unsigned w, unsigned h): width(w), height(h), channel(1){
        if(w != 0 && h!= 0) raw.resize(w*h*sizeof(T));
    }
    template <class T>
    LeapsImageLib::Image<T>::Image(unsigned w, unsigned h, unsigned c): width(w), height(h), channel(c){
        if(w != 0 && h!= 0 && c != 0) raw.resize(w*h*sizeof(T)*channel);
    }
    template <class T>
    LeapsImageLib::Image<T>::Image(unsigned w, unsigned h, unsigned c, ColorFormat cf): width(w), height(h), channel(c), colorFormat(cf){
        raw.resize(w*h*c*sizeof(T));
    }
    template <class T>
    LeapsImageLib::Image<T>::Image(const char* filename){
        std::cout << "image load only support uint8, uint16, float32, float64" << std::endl;
        throw exception();
    }

    template <>
    LeapsImageLib::Image<uint8_t>::Image(const char* filename);
    template <>
    LeapsImageLib::Image<_Float64>::Image(const char* filename);
    template <>
    LeapsImageLib::Image<_Float32>::Image(const char* filename);

    template <class T>
    T* Image<T>::ptr(unsigned row){
        return &raw[0] + ((width * row * channel * sizeof(T)));
    }
    template <class T>
    T* Image<T>::ptr(unsigned row, unsigned col){
        return &raw[0] + (width * row * channel * sizeof(T)) + col * channel * sizeof(T);
    }

    template <class T>
    void Image<T>::save(const char* filename){
        unsigned error = lodepng::encode(filename, raw, width, height);
        if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    // functions
    Image<uint8_t> rgb2gray(Image<uint8_t>& img);
    void _rgb2gray(Image<uint8_t>& img);
} /* end LeapsImageLib namepsace*/

#endif