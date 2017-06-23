//
//  dithering.h
//  Image Processing Template
//
//  Created by Ghanshyam Bhutra on 11/20/16.
//  Copyright © 2016 Ghanshyam Bhutra. All rights reserved.
//

#ifndef dithering_h
#define dithering_h

#include "cImage.hpp"
#include "cVector2d.hpp"
#include <cmath>

namespace DITHER {
    
    RGB colorThres(RGB col, int numColorsPerChannel) {
        int colorUnit = 256/numColorsPerChannel;
        short rFactor = round(get<0>(col)/colorUnit) ;
        short gFactor = round(get<1>(col)/colorUnit) ;
        short bFactor = round(get<2>(col)/colorUnit) ;
        
        return clamp(RGB{(rFactor*colorUnit), (gFactor*colorUnit), (bFactor*colorUnit)});
         
    }
    
    void toGrayScaleAVG(cImage& inputImg, cImage& outImg)  {
        short colSum = 0;
        for (int x=0;x<inputImg.getWidth();++x) {
            for (int y=0;y<inputImg.getHeight();y++) {
                auto p = inputImg.getPixelAtXY(x, y);
                colSum = p.getRed()+ p.getGreen()+ p.getBlue();
                colSum=colSum/3;
                outImg.setPixelAtXY(x, y, RGB{colSum,colSum,colSum});
            }
        }
    }
    
    void halfToning(cImage& inputImg, cImage& outImg) {
        int colSum = 0;
        outImg = cImage(inputImg.getWidth(), inputImg.getHeight(), RGB{255,255,255});
        cPixel<RGB> p(RGB{0,0,0});
        for (int x=0;x<inputImg.getWidth()-3;x+=3) {
            for (int y=0;y<inputImg.getHeight()-3;y+=3) {
                colSum = 0;
                for (int i=0;i<3;i++) {
                    for (int j =0;j<3;j++)    {
                        int w = x+i;
                        int h = y+j;
                        if (0<=w && inputImg.getWidth()>w && 0<=h && inputImg.getHeight()>h)    {
                            colSum += inputImg.getPixelAtXY(w, h).getRed();
                        }
                    }
                }
                double val = (double)colSum/(255*9);
                val = 1-val;
                if (0 < val && 0.1 > val)   {
                }
                else if (0.1 < val && 0.2 > val) {
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                }
                else if (0.2 < val && 0.3 > val){
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                }
                else if (0.3 < val && 0.4 > val) {
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                }
                else if (0.4 < val && 0.5 > val)    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                }
                else if (0.5 < val && 0.6 > val)    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                }
                else if (0.6 < val && 0.7 > val)    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                }
                else if (0.7 < val && 0.8 > val)    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+2, RGB{0,0,0});
                }
                else if (0.8 < val && 0.9 > val)    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+2, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+2, RGB{0,0,0});
                    
                }
                else    {
                    outImg.setPixelAtXY(x, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y, RGB{0,0,0});
                    outImg.setPixelAtXY(x, y+2, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+1, RGB{0,0,0});
                    outImg.setPixelAtXY(x+1, y+2, RGB{0,0,0});
                    outImg.setPixelAtXY(x+2, y+2, RGB{0,0,0});
                }
            }
        }
    }
    
    void FloydSteinbergMethod(cImage& inputImg, cImage& outImg) {
        for (int x=1;x<inputImg.getWidth()-1;++x) {
            for (int y=1;y<inputImg.getHeight()-1;y++) {
                cPixel<RGB> p = inputImg.getPixelAtXY(x,y);
                cPixel<RGB> p1 = inputImg.getPixelAtXY(x+1,y);
                cPixel<RGB> p2 = inputImg.getPixelAtXY(x-1,y+1);
                cPixel<RGB> p3 = inputImg.getPixelAtXY(x,y+1);
                cPixel<RGB> p4 = inputImg.getPixelAtXY(x+1,y+1);
                short col = p.getRed();
                col = col > 128 ? 255 : 0;
                short diff = p.getRed()-col;
                short col1 = p1.getRed();
                short col2 = p2.getRed();
                short col3 = p3.getRed();
                short col4 = p4.getRed();
                col1 +=(diff*7)/16;
                col2 +=(diff*3)/16;
                col3 +=(diff*5)/16;
                col4 +=(diff*1)/16;
                inputImg.setPixelAtXY(x+1, y, RGB{col1,col1,col1});
                inputImg.setPixelAtXY(x-1, y-1, RGB{col2,col1,col1});
                inputImg.setPixelAtXY(x, y+1, RGB{col3,col1,col1});
                inputImg.setPixelAtXY(x+1, y+1, RGB{col4,col1,col1});
                outImg.setPixelAtXY(x,y,RGB{col,col,col});
            }
        }
    }
    
    void Ordered(cImage& inputImg, cImage& outImg) {
        MATRIX::mat m3{
            {1/10,8/10,4/10},
            {7/10,6/10,3/10},
            {5/10,2/10,9/10}
        };
        MATRIX::mat m4{
            {0,8,2,10},
            {12,4,14,6},
            {3,11,1,9},
            {15,7,13,5}
        };
        for (int x=1;x<inputImg.getWidth()-1;++x) {
            for (int y=1;y<inputImg.getHeight()-1;y++) {
                short rCol = inputImg.getPixelAtXY(x,y).getRed();
                short thres = static_cast<short>((m4[x%4][y%4]+0.5)*16);
                if (rCol > thres)
                    outImg.setPixelAtXY(x,y,{255,255,255});
                else
                    outImg.setPixelAtXY(x,y,{0,0,0});
            }
        }
    }
    void OrderedKernel(cImage& inputImg, cImage& outImg, cImage& kernel) {
        double colSum=0;
        for (int x=0;x<kernel.getWidth();++x) {
            for (int y=0;y<kernel.getHeight();y++) {
                colSum += kernel.getPixelAtXY(x, y).getRed();
            }
        }
        
        for (int x=1;x<inputImg.getWidth()-1;++x) {
            for (int y=1;y<inputImg.getHeight()-1;y++) {
                short rCol = inputImg.getPixelAtXY(x,y).getRed();
                double temp = kernel.getPixelAtXY(x%kernel.getWidth(), y%kernel.getHeight()).getRed();
                temp = (temp+0.5)/255;
                short thres = static_cast<short>(temp*255);
                if (rCol > thres)
                    outImg.setPixelAtXY(x,y,{255,255,255});
                else
                    outImg.setPixelAtXY(x,y,{0,0,0});
            }
        }
    }
    
    void dotDiffusion(cImage& inputImg, cImage& outImg) {
        
        MATRIX::mat m64{
            {34,48,40,32,29,15,23,31},
            {42,58,56,53,21,5,7,10},
            {50,62,61,45,13,1,2,18},
            {38,46,54,37,25,179,26},
            {28,14,22,30,35,49,41,33},
            {20,4,6,11,43,59,57,52},
            {12,0,3,19,51,63,60,44},
            {24,16,8,27,39,47,55,36}
        };
        MATRIX::mat m4 {
            {14,13,1,2},
            {4,6,11,9},
            {0,3,15,12},
            {10,8,5,7}
        };
        for (int x=0;x<inputImg.getWidth()-1;x+=4) {
            for (int y=0;y<inputImg.getHeight()-1;y+=4) {
                for (int k=0;k<16;k++)  {
                    for (int i=0;i<4;i++)   {
                        for (int j=0;j<4;j++)   {
                            if (k==m4[i][j]) {
                                short p = inputImg.getPixelAtXY(x+i,y+j).getRed();
                                short err;
                                if (p>127)  {
                                    err = p-127;
                                    outImg.setPixelAtXY(x+i,y+j, {255,255,255});
                                }
                                else    {
                                    err = p;
                                    outImg.setPixelAtXY(x+i,y+j, {0,0,0});
                                }
                                double sumWeights = 0;
                                for (int u=-1;u<1;u++)  {
                                    for (int v=-1;v<1;v++)  {
                                        int w = x+u;
                                        int h = j+v;
                                        if (0<w && 0<h) {
                                            if ( m4[i][j] < m4[w%4][h%4])   {
                                                sumWeights=(3-pow((w-x),2)-pow((h-y),2));
                                            }
                                        }
                                    }
                                }
                                if (0<sumWeights)  {
                                    for (int u=-1;u<1;u++)  {
                                        for (int v=-1;v<1;v++)  {
                                            int w = x+u;
                                            int h = y+v;
                                            if (-1 < w && inputImg.getWidth() > w && -1 < h && inputImg.getHeight() > h) {
                                                auto pE = inputImg.getPixelAtXY(w, h).getRed();
                                                pE += static_cast<short>(err*((3-pow((w-x),2)-pow((h-y),2))/sumWeights));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void kerneled(cImage& im1, cImage& out, cImage& k)  {
        double tot = 0;
        for(int i=0;i<k.getWidth();i++)   {
            for (int j=0;j<k.getHeight();j++) {
                tot+=k.getPixelAtXY(i, j).getRed();
            }
        }
        for (int x=0;x<im1.getWidth()-1;x+=k.getWidth()) {
            for (int y=1;y<im1.getHeight()-1;y+=k.getHeight()) {
                for(int i=0;i<k.getWidth();i++)   {
                    for (int j=0;j<k.getHeight();j++) {
                        auto p = im1.getPixelAtXY(x+i,y+j);
                        short col = p.getRed();
                        if (col<80)    {
                            out.setPixelAtXY(x+i,y+j,k.getPixelAtXY(i,j));
                        }
                        else
                            out.setPixelAtXY(x+i,y+j,RGB{0,0,0});
                    }
                }
            }
        }
    }
}

#endif /* dithering_h */
