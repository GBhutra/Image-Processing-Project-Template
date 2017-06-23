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
#include "cVector2d.hpp"

/*
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
*/

#endif /* manipulation_h */
