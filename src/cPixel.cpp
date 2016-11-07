//
//  cPixel.cpp
//  ImageProcessingProjects
//
//  Created by Ghanshyam Bhutra on 10/22/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//
#include "cPixel.hpp"
using namespace std;

RGB operator+(RGB& lhs, RGB& rhs) {
    return {(get<0>(lhs)+get<0>(rhs)),(get<1>(lhs)+get<1>(rhs)),(get<2>(lhs)+get<2>(rhs))};
}

HSV operator+(HSV& lhs, HSV& rhs) {
    return {(get<0>(lhs)+get<0>(rhs)),(get<1>(lhs)+get<1>(rhs)),(get<2>(lhs)+get<2>(rhs))};
}


void cPixel::operator=(const cPixel& rhs)	{
    color = rhs.color;
}
cPixel operator+(const cPixel& lhs, const cPixel& rhs)   {
    int r = get<0>(lhs.color)+get<0>(rhs.color);
    int g = get<1>(lhs.color)+get<1>(rhs.color);
    int b = get<2>(lhs.color)+get<2>(rhs.color);
    return cPixel(r,g,b);
};

cPixel operator-(const cPixel& lhs, const cPixel& rhs)   {
    int r = get<0>(lhs.color)-get<0>(rhs.color);
    int g = get<1>(lhs.color)-get<1>(rhs.color);
    int b = get<2>(lhs.color)-get<2>(rhs.color);
    return cPixel(r,g,b);
};

HSV cPixel::toHSV()	{
	double red, green, blue,h,s,v;
    double max, min, delta;
    red 	= static_cast<double>(get<0>(color)) / 255.0;
    green 	= static_cast<double>(get<1>(color)) / 255.0;
    blue 	= static_cast<double>(get<2>(color)) / 255.0;
    
    max = maximum(red, green, blue);
    min = minimum(red, green, blue);
    
    v = max;                        /* value is maximum of r, g, b */
    if(max == 0){    /* saturation and hue 0 if value is 0 */
        return {0,0,v};
    }
    else    {
        s = (max - min) / max;           /* saturation is color purity on scale 0 - 1 */
        
        delta = max - min;
        if(delta == 0)                    /* hue doesn't matter if saturation is 0 */
            h = 0;
        else{
            if(red == max)                  /* otherwise, determine hue on scale 0 - 360 */
                h = (green - blue) / delta;
            else if(green == max)
                h = 2.0 + (blue - red) / delta;
            else                            /* (blue == max) */
                h = 4.0 + (red - green) / delta;
            h = h * 60.0;
            if(h < 0)
                h = h + 360.0;
        }
    }
    return {h,s,v};
}

static double mod(double v) {
    return v>=0?v:-v;
}
static double modulo(double v, int den) {
    int k = ((int)v)%den;
    return k+(v-(int)v);
}

//algorithm taken from http://en.wikipedia.org/wiki/HSL_and_HSV
RGB HSVtoRGB(HSV pixel)   {
    double c = get<2>(pixel)*get<1>(pixel);
    double h1 = get<0>(pixel)/60;
    double x = c*(1-mod(modulo(h1,2) - 1));
    double r1 = 0.0, g1 = 0.0, b1 = 0.0;
    
    switch((int)h1){
        case 0: r1 = c; g1 = x; b1 = 0; break;
        case 1: r1 = x; g1 = c; b1 = 0; break;
        case 2: r1 = 0; g1 = c; b1 = x; break;
        case 3: r1 = 0; g1 = x; b1 = c; break;
        case 4: r1 = x; g1 = 0; b1 = c; break;
        case 5: r1 = c; g1 = 0; b1 = x; break;
    }
    r1+=get<2>(pixel)-c;
    g1+=get<2>(pixel)-c;
    b1+=get<2>(pixel)-c;
    return (make_tuple(static_cast<int>(r1*255),static_cast<int>(g1*255),static_cast<int>(b1*255)));
}

RGB compose(RGB c1, RGB c2 ,double ratio)    {
    RGB result;
    get<0>(result) = static_cast<int>((ratio*get<0>(c1))+(1-ratio)*get<0>(c2));
    get<1>(result) = static_cast<int>((ratio*get<1>(c1))+(1-ratio)*get<1>(c2));
    get<2>(result) = static_cast<int>((ratio*get<2>(c1))+(1-ratio)*get<2>(c2));
    return result;
}
