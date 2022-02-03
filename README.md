# Development Processing

Image processing library for personal research. It aims to implement an optimized algorithm in the C++ environment.

## LEaps Color Format Architecture

The color format is newly defined as follows to suit the purpose of image processing.

| Color format | Description                                  | idx  |
| ------------ | -------------------------------------------- | ---- |
| CF_RGBA_8U   | RGBA order, 8 bit unsigned format            | 0    |
| CF_GRAY_8U   | GRAY scale(luminance), 8 bit unsigned format | 1    |
| CF_RGBA_32F  | RGBA order, 32 single precision(float)       | 2    |
| CF_RGBA_64F  | RGBA order, 64 double precision(double)      | 3    |

- 

# Development Timeline Log

## Feature Change (PM 11:23 2022-02-02)

In the past, it was implemented by integrating the color format of the fourcc and Opencv color format system. In the modified structure, v4l2 and Android (fourcc)-based color format are integrated. 

However, the fourcc type color format is not optimized for image processing. Therefore, I build a color format for image processing in my own way. It has the following regularity.

> CF\_{color format like fourcc}\_{variable type}

please see here for supported color formats [link](#LEaps-Color-Format-Architecture).



Added little-endian and big-endian processing.

## Feature Add (AM 4:47 2022-02-02)

| Name        | Description                                                  | Note |
| ----------- | ------------------------------------------------------------ | ---- |
| ColorFormat | It means color format, will be changed to fourcc             |      |
| PixelType   | To receive the byte order, it will be integrated with the color format |      |

- Todo list
  - Endian check(byte order)
  - Analyzing the Android color format system

