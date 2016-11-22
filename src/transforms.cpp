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
    mat op=identityMat(3);
    op[0][0] = cos(ang);
    op[0][1] = sin(ang);
    op[1][0] = -sin(ang);
    op[1][1] = cos(ang);
    return op;
}
mat scalingMat(double x, double y);

mat shearMat(double x, double y);
mat translationMat(double x, double y)  {
    mat op=identityMat(3);
    op[0][2] = x;
    op[1][2] = y;
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



void bilinearWarp(cImage& inputImg, cImage& outImage, vector<vector2D>& p)   {
    double a0 = p[0].first; // zero
    double a1 = p[3].first - p[0].first; // width
    double a2 = p[1].first - p[0].first; // zero
    double a3 = p[2].first - p[1].first - p[3].first + p[0].first; // 0
    
    double b0 = p[0].second; // <zero
    double b1 = p[3].second - p[0].second; // 0
    double b2 = p[1].second - p[0].second; // height
    double b3 = p[2].second - p[1].second - p[3].second + p[0].second; //0
    
    int numSamples = 20;
    double xf, yf;
    
    for(int y = 0; y < outImage.getHeight(); y++) {
        for(int x = 0; x < outImage.getWidth(); x++) {
            vector<double> totalColors(3,0);
            for (int sample = 0; sample < numSamples; sample++) {
                xf = 1.0*(x+(1.0*rand()/RAND_MAX));
                yf = 1.0*(y+(1.0*rand()/RAND_MAX));

                float c0 = a1*(b0-yf)+b1*(xf-a0); // width*-y
                float c1 = a3*(b0-yf)+b3*(xf-a0)+a1*b2-a2*b1; // width*height
                float c2 = a3*b2 - a2*b3; // zero
            
                double t1 = -c1/(2*c2);
                double t2 = (sqrt(c1*c1-4*c2*c0))/(2*c2);
                
                double v = t1+t2;
                if(v>1 || v<0)
                    v = t1-t2;
                double u = (xf-a0-a2*v)/(a1+a3*v);
                
                int V = static_cast<int>(v*inputImg.getHeight());
                int U = static_cast<int>(u*inputImg.getWidth());
                
                if (0<=U && inputImg.getWidth()>U && 0<=V && inputImg.getHeight()>V)    {
                    auto p = inputImg.getPixelAtXY(U, V);
                    totalColors[0] += p.getRed();
                    totalColors[1] += p.getGreen();
                    totalColors[2] += p.getBlue();
                }
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
    double freq = 5;
    double amp = 1;
    mat m=identityMat(3);
    for(int i=0;i<outImage.getWidth();i++)  {
        for(int j=0;j<outImage.getHeight();j++) {
            mat m=identityMat(3);
            mat destPos{{static_cast<double>(i)},{static_cast<double>(j)},{1}};
            m[0][0] = sin((2*PI/freq)*i);
            m[1][1] = sin((2*PI/freq)*j);
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
