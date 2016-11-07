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
#include <tuple>

using namespace std;

#define maximum(x, y, z) ((x) > (y)? ((x) > (z)? (x) : (z)) : ((y) > (z)? (y) : (z)))
#define minimum(x, y, z) ((x) < (y)? ((x) < (z)? (x) : (z)) : ((y) < (z)? (y) : (z)))

typedef tuple<uint8_t,uint8_t,uint8_t>RGB;
typedef tuple<double, double, double>HSV;


class cPixel	{
    RGB color;
public:
    // constructors
    cPixel() : color({0,0,0}) {};
    cPixel(uint8_t x, uint8_t y, uint8_t z) : color({x,y,z}) {};
    
    //assignment operator overload
    void operator=(const cPixel& rhs);
    
    //getters and setters
    inline uint8_t getRed()	{	return get<0>(color);	};
    inline uint8_t getGreen()	{	return get<1>(color);	};
    inline uint8_t getBlue()	{	return get<2>(color);	};
    inline RGB getColor()    {   return color;         };
    inline void setRed(uint8_t r) {	get<0>(color) = r;	};
    inline void setGreen(uint8_t g) {	get<1>(color) = g;	};
    inline void setBlue(uint8_t b) {	get<2>(color) = b;	};
    
    //function that returns the HSV value of the pixel
    HSV toHSV();
    
    //arithmetic operator overload
    friend cPixel operator+(const cPixel& lhs, const cPixel& rhs);
    friend cPixel operator-(const cPixel& lhs, const cPixel& rhs);
};

RGB HSVtoRGB(HSV pixel);
RGB compose(RGB, RGB,double);

#endif /* cPixel_hpp */
