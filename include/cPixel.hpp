//
//  cPixel.hpp
//  ImageProcessingProjects
//
//  Created by Ghanshyam Bhutra on 10/22/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef cPixel_hpp
#define cPixel_hpp

#include <iostream>
#include "utility.hpp"

using namespace std;

RGB operator+(RGB& lhs, RGB& rhs);
RGB operator-(RGB& lhs, RGB& rhs);
HSV operator+(HSV& lhs, RGB& HSV);
HSV operator-(HSV& lhs, RGB& HSV);

template<typename COLORTYPE>
class cPixel	{
    COLORTYPE val;
public:
    // constructors
    cPixel() = delete;
    cPixel(RGB col) : val(col) {};
    cPixel(HSV col) : val(col) {};
    cPixel(GS col) : val(col) {};

    COLORTYPE getColor() {
        return val;
    };
    
    //getters and setters
    short getRed();
    short getGreen();
    short getBlue();
    
    short getHue();
    double getSat();
    double getVal();
    
    short getGray();
    
    void setRed(short);
    void setGreen(short);
    void setBlue(short);
    void setHue(short);
    void setSat(double);
    void setVal(double);
    
    //function that returns the HSV value of the pixel
    cPixel<HSV> toHSV();
    cPixel<RGB> toRGB();
};


auto RGBtoInt=[](RGB col)   {
    int res = 0;
    int r = get<0>(col) << 16;
    int g = get<1>(col) << 8;
    int b = get<2>(col);
    res = r | g | b;
    return res;
};

auto IntToRGB=[](int col)   {
    RGB res;
    int mask = 0x000000FF;
    get<2>(res) = col & mask;
    get<1>(res) = (col & mask<<8)>>8;
    get<0>(res) = (col & mask<<16)>>16;
    return res;
};

auto clamp=[](RGB col) {
    short r,g,b;
    if (0>get<0>(col))
        r=0;
    else if (255<get<0>(col))
        r=255;
    else
        r = get<0>(col);
    if (0>get<1>(col))
        g=0;
    else if (255<get<1>(col))
        g=255;
    else
        g = get<1>(col);
    if (0>get<2>(col))
        b=0;
    else if (255<get<2>(col))
        b=255;
    else
        b = get<2>(col);
    return RGB{r,g,b};
};

RGB compose(RGB, RGB,double);


#endif /* cPixel_hpp */
