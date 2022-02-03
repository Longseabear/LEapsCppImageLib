
#ifndef __LEAPS_IMAGE_LIB_COLOR_CONVERTER__
#define __LEAPS_IMAGE_LIB_COLOR_CONVERTER__

#include <endian.h>
#include <stdint.h>

namespace LeapsImageLib{ /* start LeapsImageLib namepsace*/

// RGB32 color masks
#if __BYTE_ORDER == __LITTLE_ENDIAN
    static const uint32_t mAlpha8   = 0xFF000000; // RGBA
    static const uint32_t mBlue8    = 0x00FF0000;
    static const uint32_t mGreen8   = 0x0000FF00;
    static const uint32_t mRed8     = 0x000000FF;
#else
    static const uint32_t mAlpha8   = 0x000000FF; // RGBA
    static const uint32_t mBlue8    = 0x0000FF00;
    static const uint32_t mGreen8   = 0x00FF0000;
    static const uint32_t mRed8     = 0xFF000000;
#endif

// method
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define R32(rgb)    static_cast<uint8_t>(((rgb) & mRed8))
#define G32(rgb)    static_cast<uint8_t>(((rgb) & mGreen8) >> 8)
#define B32(rgb)    static_cast<uint8_t>(((rgb) & mBlue8) >> 16)
#define A32(rgb)    static_cast<uint8_t>(((rgb) & mAlpha8) >> 24)
#define R32_16(rgb)    static_cast<uint16_t>(((rgb) & mRed8))
#define G32_16(rgb)    static_cast<uint16_t>(((rgb) & mGreen8) >> 8)
#define B32_16(rgb)    static_cast<uint16_t>(((rgb) & mBlue8) >> 16)
#define A32_16(rgb)    static_cast<uint16_t>(((rgb) & mAlpha8) >> 24)
#else
#define R32(rgb)    static_cast<uint8_t>(((rgb) & mRed8) >> 24)
#define G32(rgb)    static_cast<uint8_t>(((rgb) & mGreen8) >> 16)
#define B32(rgb)    static_cast<uint8_t>(((rgb) & mBlue8) >> 8)
#define A32(rgb)    static_cast<uint8_t>(((rgb) & mAlpha8))

#define R32_16(rgb)    static_cast<uint16_t>(((rgb) & mRed8) >> 24)
#define G32_16(rgb)    static_cast<uint16_t>(((rgb) & mGreen8) >> 16)
#define B32_16(rgb)    static_cast<uint16_t>(((rgb) & mBlue8) >> 8)
#define A32_16(rgb)    static_cast<uint16_t>(((rgb) & mAlpha8))
#endif


#define RGB2Y(r, g, b) (uint8_t)(((66 * (r) + 129 * (g) +  25 * (b) + 128) >> 8) +  16)

static inline void RGBA8UToGRAY8(uint32_t rgba, uint8_t& g){
    g = RGB2Y(R32_16(rgba), G32_16(rgba), B32_16(rgba));
}

} /* end LeapsImageLib namepsace*/
#endif