//
//  transforms.hpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/31/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef transforms_hpp
#define transforms_hpp

#include <iostream>
#include "cVector2d.hpp"
#include "cImage.hpp"
#include "utility.hpp"

MATRIX::mat rotationMat(double ang);
MATRIX::mat scalingMat(double x, double y);
MATRIX::mat shearMat(double x, double y);
MATRIX::mat translationMat(double x, double y);
MATRIX::mat perspectiveMat(double x, double y);

void forwardTransform(cImage& inputImg, cImage& outImage, MATRIX::mat& m, std::function<MATRIX::mat(MATRIX::mat)>);
void inverseTransform(cImage& inputImg, cImage& outImage, MATRIX::mat& m);
void interestingTransform(cImage& inputImg, cImage& outImage);
void bilinearWarp(cImage& inputImg, cImage& outImage, vector<VECTOR::vec2D>&);

namespace TRANSFORM {
    void scale(cImage& in, cImage& out, double x, double y);
    void scaleW(cImage&, cImage&, double);
    void scaleH(cImage&, cImage&, double);
    
    void rotateZ(cImage& in, cImage& out, double deg, VECTOR::vec2D p=VECTOR::vec2D(0,0));
    
    void translateX(cImage&, cImage&, double);
    void translateY(cImage&, cImage&, double);
    void translate(cImage&, cImage&, double, double);
    
    void shearX(cImage&, cImage&, double);
    void shearY(cImage&, cImage&, double);
    void shear(cImage&, cImage&, double, double);
    
    void perspective(cImage&, cImage&, double, double);
}

#endif /* transforms_hpp */
