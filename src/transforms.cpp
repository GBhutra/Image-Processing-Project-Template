//
//  transforms.cpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/31/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "transforms.hpp"

mat rotationMat(double ang) {
    ang = DEGToRAD(ang);
    mat op(3,vector<double>(3,0));
    op[0][0] = cos(ang);
    op[0][1] = sin(ang);
    op[1][0] = -sin(ang);
    op[1][1] = cos(ang);
    op[2][2] = 1;
    return op;
}
mat scalingMat(double x, double y);

mat shearMat(double x, double y);
mat translationMat(double x, double y)  {
    mat op(3,vector<double>(3,0));
    op[0][0] = 1;
    op[0][2] = x;
    op[1][1] = 1;
    op[1][2] = y;
    op[2][2] = 1;
    return op;
}
mat perspectiveMat(double x, double y);

void forwardTransform (cImage& inputImg, cImage& outImage, mat& m)  {
    for(int i=0;i<inputImg.getWidth();i++)  {
        for(int j=0;j<inputImg.getHeight();j++) {
            mat currPos{{static_cast<double>(i)},{static_cast<double>(j)},{1}};
            mat finalPos = m*currPos;
            if (0<=finalPos[0][0] && outImage.getWidth()>finalPos[0][0])    {
                if (0<=finalPos[1][0] && outImage.getHeight()>finalPos[1][0])    {
                    auto p = inputImg.getPixelAtXY(i, j);
                    RGB col{p.getRed(),p.getGreen(),p.getBlue()};
                    outImage.setPixelAtXY(static_cast<int>(finalPos[0][0]),static_cast<int>(finalPos[1][0]), col);
                }
            }
        }
    }
}


void inverseTransform (cImage& inputImg, cImage& outImage, mat& mF)  {
    mat m = inverse(mF);
    for(int i=0;i<outImage.getWidth();i++)  {
        for(int j=0;j<outImage.getHeight();j++) {
            mat destPos{{static_cast<double>(i)},{static_cast<double>(j)},{1}};
            mat initialPos = m*destPos;
            if (0<=initialPos[0][0] && inputImg.getWidth()>initialPos[0][0])    {
                if (0<=initialPos[1][0] && inputImg.getHeight()>initialPos[1][0])    {
                    auto p = inputImg.getPixelAtXY(static_cast<int>(initialPos[0][0]),static_cast<int>(initialPos[1][0]));
                    outImage.setPixelAtXY(i,j,p);
                }
            }
        }
    }
}



void bilinear(cImage& inputImg, cImage& outImage)   {
    vector2D p0{70, 100};
    vector2D p1{900, 50};
    vector2D p2{320, 500};
    vector2D p3{720, 600};
    //p0(70, 100), p1(900, 50), p2(320, 500), p3(720, 600).
    
    double a0 = p0.first; // zero
    double a1 = p3.first - p0.first; // width
    double a2 = p1.first - p0.first; // zero
    double a3 = p2.first - p1.first - p3.first + p0.first; // 0
    
    double b0 = p0.second; // <zero
    double b1 = p3.second - p0.second; // 0
    double b2 = p1.second - p0.second; // height
    double b3 = p2.second - p1.second - p3.second + p0.second; //0
    
    
    int numSamples = 20;
    double u, v, xf, yf;
    
    for(int y = 0; y < inputImg.getHeight(); y++) {
        for(int x = 0; x < inputImg.getWidth(); x++) {
            vector<double> totalColors(3,0);
            for (int sample = 0; sample < numSamples; sample++) {
                xf = 1.0*(x+(1.0*rand()/RAND_MAX));
                yf = 1.0*(y+(1.0*rand()/RAND_MAX));
                float c0 = a1*(b0-yf)+b1*(xf-a0); // width*-y
                float c1 = a3*(b0-yf)+b3*(xf-a0)+a1*b2-a2*b1; // width*height
                float c2 = a3*b2 - a2*b3; // zero
                if(fabs(c2) <= 0.001){
                    v = (a1 * yf - a1 * b0 - b1 * xf + a0 * b1) / (a1 * b2 - a2 * b1);
                    u = (xf - a0 - a2 * v) / a1;
                }
                else {
                    float discriminant = sqrt(c1*c1-4.0*c2*c0); // width*height
                    if (c1*c1-4.0*c2*c0 < 0){discriminant = 0;}
                    v = (-c1+discriminant)/(2.0*c2); // 0
                    
                    if(v < 0.0 || v > 1.0){
                        v =(-c1 - discriminant) / (2.0 * c2);
                        u = (xf - a0 - a2 * v) / (a1 + a3 * v);
                    }
                    else{
                        u = (xf - a0 - a2 * v) / (a1 + a3 * v);
                        if(u < 0.0 || u > 1.0){
                            v =(-c1 - discriminant) / (2.0 * c2);
                            u = (xf - a0 - a2 * v) / (a1 + a3 * v);
                        }
                    }
                }
                
                v = v * (inputImg.getHeight() - 1);
                u = u * inputImg.getWidth();
                
                u = 0 > u ? -u : u;
                
                int V = (static_cast<int>(v) + inputImg.getHeight()) % inputImg.getHeight();
                int U = (static_cast<int>(u) + inputImg.getWidth()) % inputImg.getWidth();
                
                auto p = inputImg.getPixelAtXY(U, V);
                totalColors[0] += p.getRed();
                totalColors[1] += p.getGreen();
                totalColors[2] += p.getBlue();
            }
            RGB col{
                static_cast<int>(totalColors[0]/numSamples),
                static_cast<int>(totalColors[1]/numSamples),
                static_cast<int>(totalColors[2]/numSamples)
            };
            outImage.setPixelAtXY(x, y, col);
        }
    }
}

void interestingTransform(cImage& inputImg, cImage& outImage)    {
    
}
