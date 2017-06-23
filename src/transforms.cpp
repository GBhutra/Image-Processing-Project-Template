//
//  transforms.cpp
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 10/31/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#include "transforms.hpp"

using namespace MATRIX;
using namespace VECTOR;

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

//Scale transformations
void TRANSFORM::scaleW(cImage &in, cImage &out, double x)   {   scale(in,out,x,1);  }
void TRANSFORM::scaleH(cImage &in, cImage &out, double y) {   scale(in,out,1,y);  }
void TRANSFORM::scale(cImage &in, cImage &out, double x, double y)   {
    MATRIX::mat mat {
        {x,0},
        {0,y}
    };
    double det = MATRIX::det(mat);
    mat[0][0] = y/det;
    mat[1][1] = x/det;
    inverseTransform(in, out, mat);
}

void TRANSFORM::rotateZ(cImage& in, cImage& out, double deg, vec2D p)  {
    deg = DEGToRAD(deg);
    MATRIX::mat mat {
        {cos(deg),-sin(deg),(p.getX()-(p.getX()*cos(deg))+(p.getY()*sin(deg)))},
        {sin(deg),cos(deg),(p.getY()-(p.getX()*sin(deg))-(p.getY()*cos(deg)))},
        {0,0,1}
    };
    MATRIX::mat op = MATRIX::inverse(mat);
    inverseTransform(in, out, op);
}

void TRANSFORM::translateX(cImage &in, cImage &out, double x)   {   translate(in,out,x,0);  }
void TRANSFORM::translateY(cImage &in, cImage &out, double y)   {   translate(in,out,0,y);  }
void TRANSFORM::translate(cImage &in, cImage &out, double x, double y)   {
    MATRIX::mat mat {
        {1,0,x},
        {0,1,y},
        {0,0,1}
    };
    MATRIX::mat op = MATRIX::inverse(mat);
    inverseTransform(in, out, op);
}

void TRANSFORM::shearX(cImage &in, cImage &out, double x)   {   translate(in,out,x,0);  }
void TRANSFORM::shearY(cImage &in, cImage &out, double y)   {   translate(in,out,0,y);  }
void TRANSFORM::shear(cImage &in, cImage &out, double x, double y)   {
    MATRIX::mat mat {
        {1,x},
        {y,1}
    };
    double det = MATRIX::det(mat);
    if (0!=det) {
        mat[0][0] = mat[1][1]/det;
        mat[0][1] = -mat[0][1]/det;
        mat[1][0] = -mat[1][0]/det;
        mat[1][1] = mat[0][0]/det;
        inverseTransform(in, out, mat);
    }
}

void TRANSFORM::perspective(cImage &in, cImage &out, double x, double y)   {
    MATRIX::mat mat {
        {1,0,0},
        {0,1,0},
        {x,y,1}
    };
    auto f = [](MATRIX::mat m) {
        m[0][0] = m[0][0]/m[2][0];
        m[1][0] = m[1][0]/m[2][0];
        return m;
    };
    forwardTransform(in, out, mat,f);
}

void inverseTransform(cImage& inputImg, cImage& outImage, MATRIX::mat& m)   {
    if (2==m.size())    {
        for(int x=0;x<outImage.getWidth();x++)  {
            for(int y=0;y<outImage.getHeight();y++) {
                MATRIX::mat outLoc{
                    {static_cast<double>(x)},
                    {static_cast<double>(y)}
                };
                mat inLoc = m*outLoc;
                if (0<=inLoc[0][0] && inputImg.getWidth()>inLoc[0][0] && 0<=inLoc[1][0] && inputImg.getHeight()>inLoc[1][0])    {
                    auto p = inputImg.getPixelAtXY(static_cast<int>(inLoc[0][0]), static_cast<int>(inLoc[1][0]));
                    outImage.setPixelAtXY(x, y, p);
                }
            }
        }
    }
    if (3==m.size())    {
        for(int x=0;x<outImage.getWidth();x++)  {
            for(int y=0;y<outImage.getHeight();y++) {
                MATRIX::mat outLoc{
                    {static_cast<double>(x)},
                    {static_cast<double>(y)},
                    {1}
                };
                mat inLoc = m*outLoc;
                if (0<=inLoc[0][0] && inputImg.getWidth()>inLoc[0][0] && 0<=inLoc[1][0] && inputImg.getHeight()>inLoc[1][0])    {
                    auto p = inputImg.getPixelAtXY(static_cast<int>(inLoc[0][0]), static_cast<int>(inLoc[1][0]));
                    outImage.setPixelAtXY(x, y, p);
                }
            }
        }
    }
}
void forwardTransform(cImage& inputImg, cImage& outImage, MATRIX::mat& m, std::function<MATRIX::mat(MATRIX::mat)> step2)   {
    for(int x=0;x<inputImg.getWidth();x++)  {
        for(int y=0;y<inputImg.getHeight();y++) {
            MATRIX::mat inLoc{
                {static_cast<double>(x)},
                {static_cast<double>(y)},
                {1}
            };
            mat outLoc = m*inLoc;
            outLoc = step2(outLoc);
            if (0<=outLoc[0][0] && outImage.getWidth()>outLoc[0][0] && 0<=outLoc[1][0] && outImage.getHeight()>outLoc[1][0])    {
                auto p = inputImg.getPixelAtXY(x, y);
                outImage.setPixelAtXY(static_cast<int>(outLoc[0][0]), static_cast<int>(outLoc[1][0]), p);
            }
        }
    }
}


void bilinearWarp(cImage& inputImg, cImage& outImage, vector<vec2D>& p)   {
    double a0 = p[0].getX(); // zero
    double a1 = p[3].getX() - p[0].getX(); // width
    double a2 = p[1].getX() - p[0].getX(); // zero
    double a3 = p[2].getX() - p[1].getX() - p[3].getX() + p[0].getX(); // 0
    
    double b0 = p[0].getY(); // <zero
    double b1 = p[3].getY() - p[0].getY(); // 0
    double b2 = p[1].getY() - p[0].getY(); // height
    double b3 = p[2].getY() - p[1].getY() - p[3].getY() + p[0].getY(); //0
    
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
/*
 void interestingTransform(cImage& inputImg, cImage& outImage)    {
 double freq = 5;
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
 }*/
