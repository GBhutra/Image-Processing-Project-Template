//
//  manipulation.hpp
//  pr04
//
//  Created by Ghanshyam Bhutra on 10/16/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef manipulation_h
#define manipulation_h

#include "cPixel.hpp"
#include "cImage.hpp"
#include "histogram.hpp"
#include "vector2d.hpp"


double h0(double t){	return 2*t*t*t - 3*t*t + 1;}
double h1(double t){	return (-2)*t*t*t + 3*t*t ;}
double h2(double t){	return t*t*t - 2*t*t + t;}
double h3(double t){	return t*t*t - t*t ;}

cImage replaceHue(cImage& inputFile, cImage& controlFile) {
    for (int i=0;i<inputFile.getHeight();++i) {
        for (int j=0;j<inputFile.getWidth();++j) {
            cPixel pI = inputFile.getPixelAtXY(i,j);
            cPixel pC = controlFile.getPixelAtXY(i,j);
            HSV iF = pI.toHSV();
            HSV cF = pC.toHSV();
            RGB col = HSVtoRGB({get<0>(cF),get<1>(iF),get<2>(iF)});
            inputFile.setPixelAtXY(i, j, col);
        }
    }
    return inputFile;
};


#endif /* manipulation_h */
